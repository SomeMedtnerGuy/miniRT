/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:07:10 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/10 15:21:36 by ndo-vale         ###   ########.fr       */
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
