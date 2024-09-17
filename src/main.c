/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:07:10 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/17 16:44:27 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point_light	point_light(t_tup4 position, t_tup4 intensity)
{
	t_point_light	out;

	out.position = position;
	out.intensity = intensity;
	return (out);
}

t_material	material(void)
{
	t_material	out;

	out.color = color(1, 1, 1);
	out.diffuse = 0.9;
	out.specular = 0.9;
	out.shininess = 200.0;
	return (out);
}

t_matrix4	define_transf_matrix(int transf_type, int change_dir)
{
	t_matrix4	out;
	
	if (transf_type == ROTATEX)
		out = rotation_x(M_PI / 16);
	else if (transf_type == ROTATEY)
		out = rotation_y(M_PI / 16);
	else if (transf_type == ROTATEZ)
		out = rotation_z(M_PI / 16);
	else if (transf_type == SCALEX)
		out = scaling(1.1, 1, 1);
	else if (transf_type == SCALEY)
		out = scaling(1, 1.1, 1);
	else if (transf_type == SCALEZ)
		out = scaling(1, 1, 1.1);
	else if (transf_type == TRANSLATEX)
		out = translation(1, 0, 0);
	else if (transf_type == TRANSLATEY)
		out = translation(0, 1, 0);
	else if (transf_type == TRANSLATEZ)
		out = translation(0, 0, 1);
	if (change_dir == -1)
		out = invert_matrix4(out);
	return (out);
}

t_matrix4	include_new_transformation(t_matrix4 tr_obj, t_matrix4 tr_new, t_transf_type t_type)
{
	t_matrix4	current_translation;
	
	current_translation = translation(tr_obj.e[0][3], tr_obj.e[1][3], tr_obj.e[2][3]);
	tr_obj = multiply_matrix4(invert_matrix4(current_translation), tr_obj);
	if (t_type == SCALEX || t_type == SCALEY || t_type == SCALEZ)
		tr_obj = multiply_matrix4(tr_obj, tr_new);
	else
		tr_obj = multiply_matrix4(tr_new, tr_obj);
	return (multiply_matrix4(current_translation, tr_obj));
}

void	apply_transformation(t_root *r, int change_dir)
{
	t_matrix4	transf_matrix;
	t_shape		*shape;
	
	if (r->transf_type == NO_TRANSFORM_TYPE)
		return ;
	transf_matrix = define_transf_matrix(r->transf_type, change_dir);
	if (r->current_object == CAMERA)
		/*r->world->camera->transform = include_new_transformation(r->world->camera->transform,
			transf_matrix, r->transf_type);*/
		r->world->camera->transform = multiply_matrix4(transf_matrix, r->world->camera->transform);
	else if (r->current_object == LIGHT)
		r->world->light.position = matrix4_mult_tup4(transf_matrix,
			r->world->light.position);
	else if (r->current_shape)
	{
		shape = (t_shape *)r->current_shape->content;
		shape->transform = include_new_transformation(shape->transform,
			transf_matrix, r->transf_type);
		shape->i_transform = invert_matrix4(shape->transform);
	}
	printf("%p\n", r->current_shape);
	render(r);
}

void	select_object(t_obj_type type, t_root *r)
{
	if (r->current_object == LIGHT)
		r->world->light.intensity = multiply_tup4(r->world->light.intensity, 1.0/2.0);
	else if (r->current_object == SHAPE && r->current_shape)
	{
		((t_shape *)r->current_shape->content)->material.diffuse *= 1.0/2.0;
		printf("%f\n", ((t_shape *)r->current_shape->content)->material.diffuse);
	}
	r->current_object = type;
	if (type == LIGHT)
		r->world->light.intensity = multiply_tup4(r->world->light.intensity, 2.0);
	else if (type == SHAPE)
	{
		if (r->current_shape)
			r->current_shape = r->current_shape->next;
		else
			r->current_shape = r->world->objects;
		if (r->current_shape)
		{
			((t_shape *)r->current_shape->content)->material.diffuse *= 2;
			printf("%f\n", ((t_shape *)r->current_shape->content)->material.diffuse);
		}
	}
	render(r);
}

int	key_hook(int keycode, t_root *r)
{
	if (!r->allowed_transf)
		return (0);
	if (keycode == 65307)
		clean_exit(r, 0);
	else if (keycode == XK_c)
		select_object(CAMERA, r);
		//r->current_object = CAMERA;
	else if (keycode == XK_l)
		select_object(LIGHT, r);
		//r->current_object = LIGHT;
	else if (keycode == XK_s)
	{
		select_object(SHAPE, r);
		/*r->current_object = SHAPE;
		if (r->current_shape)
			r->current_shape = r->current_shape->next;
		else
			r->current_shape = r->world->objects;*/
	}
	else if (keycode == XK_Left)
	{
		if (r->transf_type <= 0)
			r->transf_type = 10;
		r->transf_type = (r->transf_type - 1);
		printf("Current transform type: %i\n", r->transf_type);
	}
	else if (keycode == XK_Right)
	{
		r->transf_type = (r->transf_type + 1) % TRANSF_TYPE_AM;
		ft_printf("Current transform type: %i\n", r->transf_type);
	}
	else if (keycode == XK_Up)
	{
		r->allowed_transf = false;
		apply_transformation(r, 1);
		r->allowed_transf = true;
	}
	else if (keycode == XK_Down)
	{
		r->allowed_transf = false;
		apply_transformation(r, -1);
		r->allowed_transf = true;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_root	r;
	char	*extension;

	if (argc != 2)
		return (ft_putstr_fd(WRONG_USAGE_MSG, 2), 1);
	extension = ft_substr(argv[1], ft_strlen(argv[1]) - 3, 3);
	if (strcmp(extension, ".rt") != 0)
		return (free(extension), ft_putstr_fd(FILE_EXT_MSG, 2), 1);
	free(extension);
	r.world = world();
	r.transf_type = ROTATEX;
	r.current_object = INVALID_OBJ;
	r.current_shape = NULL;
	r.allowed_transf = true;
	parse_config_file(argv[1], &r);
	r.mlx = mlx_init();
	r.win = mlx_new_window(r.mlx, CANVAS_WIDTH, CANVAS_HEIGHT, WINDOW_TITLE);
	r.canvas = (t_canvas *)ft_calloc(1, sizeof(t_canvas));
	r.canvas->img = mlx_new_image(r.mlx, CANVAS_WIDTH, CANVAS_HEIGHT);
	r.canvas->addr = mlx_get_data_addr(r.canvas->img, &r.canvas->bits_per_pixel,
			&r.canvas->line_length, &r.canvas->endian);
	render(&r);
	mlx_key_hook(r.win, key_hook, &r);
	mlx_hook(r.win, DestroyNotify, 0L, clean_exit, &r);
	mlx_loop(r.mlx);
}
