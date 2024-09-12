/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:07:10 by ndo-vale          #+#    #+#             */

/*   Updated: 2024/09/11 14:20:29 by ndo-vale         ###   ########.fr       */
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

t_material	*material(void)
{
	t_material	*out;

	out = ft_calloc(1, sizeof(t_material));
	out->color = color(1, 1, 1);
	//out->ambient = 0.1;
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
	char	*extension;

	if (argc != 2)
		return (ft_putstr_fd(WRONG_USAGE_MSG, 2), 1);
	extension = ft_substr(argv[1], ft_strlen(argv[1]) - 3, 3);
	if (strcmp(extension, ".rt") != 0)
		return (free(extension), ft_putstr_fd(FILE_EXT_MSG, 2), 1);
	free(extension);
	parse_config_file(argv[1], &r);
	//print_tup4(r.world->light.intensity, false);

	r.mlx = mlx_init();
	r.win = mlx_new_window(r.mlx, CANVAS_WIDTH, CANVAS_HEIGHT, WINDOW_TITLE);
	r.canvas = (t_canvas *)ft_calloc(1, sizeof(t_canvas));
	r.canvas->img = mlx_new_image(r.mlx, CANVAS_WIDTH, CANVAS_HEIGHT);
	r.canvas->addr = mlx_get_data_addr(r.canvas->img, &r.canvas->bits_per_pixel,
			&r.canvas->line_length, &r.canvas->endian);

	/*t_shape	*middle = (t_shape *)plane();

	
	//((t_plane *)middle)->normal = vector(0, 0, -1);
	//set_transform(middle, translation(0, 0, 10));
	print_matrix4(get_target_rotation(vector(0, 0, -1)), false);
	print_matrix4(rotation_x(M_PI / 2), false);
	set_transform(middle, multiply_matrix4(translation(0, 0, 10), get_target_rotation(vector(0, 0, 1))));
	
	
	middle->material = material();
	middle->material->color = color(0.1, 1, 0.5);
	r.world->light = point_light(point(2, 2, -4), color(1, 1, 1));
	r.camera = camera(CANVAS_WIDTH, CANVAS_HEIGHT, M_PI / 3);
	r.camera->transform = view_transform(point(0, 0, -5), point(0, 0, 1), vector(0, 1, 0));
	ft_lstadd_back(&r.world->objects, ft_lstnew(middle));*/
	
	
	render(r.canvas, r.camera, r.world);

	mlx_put_image_to_window(r.mlx, r.win, r.canvas->img, 0, 0);
	mlx_key_hook(r.win, key_hook, &r);
	mlx_hook(r.win, DestroyNotify, 0L, clean_exit, &r);
	mlx_loop(r.mlx);
}

