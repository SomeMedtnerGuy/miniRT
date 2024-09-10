/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 08:48:43 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/10 15:30:15 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_scene(t_root *r, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if(fd < 0)
	{
		ft_putstr_fd("Error: couldn't open file\n", STDERR_FILENO);
		return (1);
	}
	if (ft_strnrcmp(file, ".rt", 3) != 0)
		ft_putstr_fd("Error: wrong file format\n", STDERR_FILENO);
	line = get_next_line(fd);
	while(line)
	{
		parse_line(line, r);
		line = get_next_line(fd);
	}
	close(fd);
}

int	key_hook(int keycode, t_root *r)
{
	if (keycode == 65307)
		clean_exit(r, 0);
	return (0);
}

void	init_window(t_root *r)
{
	r->mlx = mlx_init();
	r->win = mlx_new_window(r->mlx, CANVAS_WIDTH, CANVAS_HEIGHT, WINDOW_TITLE);
	r->canvas = (t_canvas *)ft_calloc(1, sizeof(t_canvas));
	r->canvas->img = mlx_new_image(r->mlx, CANVAS_WIDTH, CANVAS_HEIGHT);
	r->canvas->addr = mlx_get_data_addr(r->canvas->img, &r->canvas->bits_per_pixel,
			&r->canvas->line_length, &r->canvas->endian);
}

int	main(int ac, char **av)
{
	t_root		r;

	if (ac != 2)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", STDERR_FILENO);
	}
	init_window(&r);

	create_scene(&r, av[1]);

	render(r.canvas, r.camera, r.world);
	mlx_put_image_to_window(r.mlx, r.win, r.canvas->img, 0, 0);
	mlx_key_hook(r.win, key_hook, &r);
	mlx_hook(r.win, DestroyNotify, 0L, clean_exit, &r);
	mlx_loop(r.mlx);
	return (0);
}
