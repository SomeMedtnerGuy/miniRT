/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:07:10 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/02 21:36:38 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pixel(t_canvas *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	sphere_testing();
}

/*int	main(int argc, char **argv)
{
	t_root	r;

	r.mlx = mlx_init();
	r.win = mlx_new_window(r.mlx, CANVAS_WIDTH, CANVAS_HEIGHT, WINDOW_TITLE);
	r.canvas = (t_canvas *)ft_calloc(1, sizeof(t_canvas));
	r.canvas->img = mlx_new_image(r.mlx, CANVAS_WIDTH, CANVAS_HEIGHT);
	r.canvas->addr = mlx_get_data_addr(r.canvas->img, &r.canvas->bits_per_pixel,
					&r.canvas->line_length, &r.canvas->endian);
	if (test_chapter_1(argc, argv, r.canvas) != 0)
		clean_exit(&r, 1);
	mlx_put_image_to_window(r.mlx, r.win, r.canvas->img, 0, 0);
	mlx_hook(r.win, DestroyNotify, 0L, clean_exit, &r);
	mlx_loop(r.mlx);
}*/
