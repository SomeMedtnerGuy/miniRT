/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:07:10 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/31 15:37:01 by ndo-vale         ###   ########.fr       */
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
	//t_matrix3	test3;
	t_matrix4	test1;
	t_matrix4	test2;
	t_matrix4	result;

	test1 = matrix4(tup4(1, 2, 3, 4), tup4(5, 6, 7, 8),
					tup4(9, 8, 7, 6), tup4(5, 4, 3, 2));
	test2 = matrix4(tup4(-2, 1, 2, 3), tup4(3, 2, 1, -1),
					tup4(4, 3, 6, 5), tup4(1, 2, 7, 8));

	result = multiply_matrix4(test1, test2);

	print_matrix4(result, true);
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
