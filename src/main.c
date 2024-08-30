/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:07:10 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/30 18:00:04 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	clamp(int n, int min, int max)
{
	if (n > max)
		return (max);
	if (n < min)
		return (min);
	return (n);
}

void	put_pixel(t_canvas *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


unsigned char	float_to_shade(float color_strength)
{
	return ((unsigned char)clamp((int)(color_strength * 255.0),
			0, 255));
}

int	tuple_to_color(t_tup4 tup4)
{
	return (float_to_shade(tup4.r) << 16 |
			float_to_shade(tup4.g) << 8 |
			float_to_shade(tup4.b));
}

void	print_tup3(t_tup3 a, bool cast_to_int)
{
	if (cast_to_int)
	{
		printf("| %i | %i | %i |\n",
				(int)a.e[0], (int)a.e[1], (int)a.e[2]);
	}
	else
		printf("| %f | %f | %f |\n", a.e[0], a.e[1], a.e[2]);
}

void	print_tup4(t_tup4 a, bool cast_to_int)
{
	if (cast_to_int)
	{
		printf("| %i | %i | %i | %i |\n",
				(int)a.x, (int)a.y, (int)a.z, (int)a.w);
	}
	else
		printf("| %f | %f | %f | %f |\n", a.x, a.y, a.z, a.w);
}

void	print_matrix3(t_matrix3 a, bool cast_to_int)
{
	int	i;

	i = -1;
	while (++i < 3)
		print_tup3(a.t[i], cast_to_int);
}

void	print_matrix4(t_matrix4 a, bool cast_to_int)
{
	int	i;

	i = -1;
	while (++i < 4)
		print_tup4(a.t[i], cast_to_int);
}

int	main(void)
{
	t_matrix3	test3;
	t_matrix4	test1;
	t_matrix4	test2;

	test1 = matrix4(tup4(-5, 2, 6, -8), tup4(1, -5, 1, 8),
					tup4(7, 7, -6, -7), tup4(1, -3, 7, 4));
	test2 = matrix4(tup4(1, 2, 3, 4), tup4(5, 6, 7, 8),
					tup4(9, 10, 11, 12), tup4(13, 14, 15, 16));
	test3 = matrix3(tup3(3, 5, 0), tup3(2, -1, -7), tup3(6, -1, 5));
	//printf("%f\n", determinant4(test1));
	print_matrix4(invert_matrix4(test1), false);
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
