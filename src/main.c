/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:07:10 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/10 17:28:27 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point_light	*point_light(t_tup4 position, t_tup4 intensity)
{
	t_point_light	*out;

	out = (t_point_light *)ft_calloc(1, sizeof(t_point_light));
	out->position = position;
	out->intensity = intensity;
	return (out);
}

t_material	*material(void)
{
	t_material	*out;

	out = ft_calloc(1, sizeof(t_material));
	out->color = color(1, 1, 1);
	out->ambient = 0.1;
	out->diffuse = 0.9;
	out->specular = 0.9;
	out->shininess = 200.0;
	return (out);
}

int	key_hook(int keycode, t_root *r)
{
	if (keycode == 65307)
		clean_exit(r, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_root	r;

	(void)argc;
	(void)argv;
	r.mlx = mlx_init();
	r.win = mlx_new_window(r.mlx, CANVAS_WIDTH, CANVAS_HEIGHT, WINDOW_TITLE);
	r.canvas = (t_canvas *)ft_calloc(1, sizeof(t_canvas));
	r.canvas->img = mlx_new_image(r.mlx, CANVAS_WIDTH, CANVAS_HEIGHT);
	r.canvas->addr = mlx_get_data_addr(r.canvas->img, &r.canvas->bits_per_pixel,
			&r.canvas->line_length, &r.canvas->endian);
	mlx_put_image_to_window(r.mlx, r.win, r.canvas->img, 0, 0);
	mlx_key_hook(r.win, key_hook, &r);
	mlx_hook(r.win, DestroyNotify, 0L, clean_exit, &r);
	mlx_loop(r.mlx);
}

/* int	main(int argc, char **argv)
{
	t_root	r;
@@ -44,86 +53,9 @@ int	main(int argc, char **argv)
	r.canvas = (t_canvas *)ft_calloc(1, sizeof(t_canvas));
	r.canvas->img = mlx_new_image(r.mlx, CANVAS_WIDTH, CANVAS_HEIGHT);
	r.canvas->addr = mlx_get_data_addr(r.canvas->img, &r.canvas->bits_per_pixel,
					&r.canvas->line_length, &r.canvas->endian);

	// TEST //
	t_shape	*floor;
	t_shape	*left_wall;
	t_shape		*right_wall;
	t_shape	*middle;
	t_shape	*right;
	t_shape	*left;
	t_world		*w;
	t_camera	*c;

	floor = (t_shape *)sphere();
	set_transform(floor, scaling(10, 0.01, 10));
	floor->material = material();
	floor->material->color = color(1, 0.9, 0.9);
	floor->material->specular = 0;

	left_wall = (t_shape *)sphere();
	set_transform(left_wall, multiply_matrix4(translation(0, 0, 5),
				multiply_matrix4(rotation_y(-M_PI / 4), 
				multiply_matrix4(rotation_x(M_PI / 2), scaling(10, 0.01, 10)))));
	left_wall->material = floor->material;

	right_wall = (t_shape *)sphere();
	set_transform(right_wall, multiply_matrix4(translation(0, 0, 5),
				multiply_matrix4(rotation_y(M_PI / 4), 
				multiply_matrix4(rotation_x(M_PI / 2), scaling(10, 0.01, 10)))));
	right_wall->material = floor->material;

	middle = (t_shape *)sphere();
	set_transform(middle, translation(-0.5, 1, 0.5));
	middle->material = material();
	middle->material->color = color(0.1, 1, 0.5);
	middle->material->diffuse = 0.7;
	middle->material->specular = 0.3;
	//((t_cylinder *)middle)->maximum = 1;
	//((t_cylinder *)middle)->minimum = 0.5;
	//((t_cylinder *)middle)->closed = true;

	right = (t_shape *)cylinder();
	set_transform(right, multiply_matrix4(translation(1.5, 0.5, -0.5),
						multiply_matrix4(rotation_x(M_PI / 4),
						scaling(0.5, 0.5, 0.5))));
	right->material = material();
	right->material->color = color(0.5, 1, 0.1);
	right->material->diffuse = 0.7;
	right->material->specular = 0.3;
	((t_cylinder *)right)->maximum = 1;
	((t_cylinder *)right)->minimum = 0;
	((t_cylinder *)right)->closed = true;

	left = (t_shape *)sphere();
	set_transform(left, multiply_matrix4(translation(-1.5, 0.33, -0.75),
						scaling(0.33, 0.33, 0.33)));
	left->material = material();
	left->material->color = color(1, 0.8, 0.1);
	left->material->diffuse = 0.7;
	left->material->specular = 0.3;
	//((t_cylinder *)left)->maximum = 1;
	//((t_cylinder *)left)->minimum = 0;
	//((t_cylinder *)left)->closed = true;

	w = world();
	ft_lstadd_back(&w->objects, ft_lstnew(floor));
	ft_lstadd_back(&w->objects, ft_lstnew(left_wall));
	ft_lstadd_back(&w->objects, ft_lstnew(right_wall));
	ft_lstadd_back(&w->objects, ft_lstnew(middle));
	ft_lstadd_back(&w->objects, ft_lstnew(right));
	ft_lstadd_back(&w->objects, ft_lstnew(left));
	w->light = point_light(point(-10, 5, -15), color(1, 1, 1));
	c = camera(CANVAS_WIDTH, CANVAS_HEIGHT, M_PI / 3);
	c->transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

	//printf("%f\n", ((t_shape *)w->objects->content)->transform)
	render(r.canvas, c, w);
	// ENDTEST //

			&r.canvas->line_length, &r.canvas->endian);
	mlx_put_image_to_window(r.mlx, r.win, r.canvas->img, 0, 0);
	mlx_key_hook(r.win, key_hook, &r);
	mlx_hook(r.win, DestroyNotify, 0L, clean_exit, &r);
	mlx_loop(r.mlx);
} */
