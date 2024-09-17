/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:07:10 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/17 16:01:04 by joamonte         ###   ########.fr       */
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

void	set_curr_obj(int keycode, t_root *r)
{
	if (keycode == XK_c)
		r->current_object = CAMERA;
	else if (keycode == XK_l)
		r->current_object = LIGHT;
	else if (keycode == XK_s)
	{
		r->current_object = SHAPE;
		if (r->current_shape)
			r->current_shape = r->current_shape->next;
		else
			r->current_shape = r->world->objects;
	}
}

int	key_hook(int keycode, t_root *r)
{
	if (keycode == XK_Escape)
		clean_exit(r, 0);
	else if (keycode == XK_c || keycode == XK_l || keycode == XK_s)
		set_curr_obj(keycode, r);
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
		apply_transformation(r, 1);
	else if (keycode == XK_Down)
		apply_transformation(r, -1);
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
