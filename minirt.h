/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:35:42 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/02 19:53:09 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include "mlx_linux/mlx_int.h"
# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include "libftmatrix/libftmatrix.h"

# define CANVAS_WIDTH 900
# define CANVAS_HEIGHT 500

# define WINDOW_TITLE "miniRT"

typedef struct s_ray
{
	t_tup4	origin;
	t_tup4	direction;
}	t_ray;

typedef struct s_sphere //Acrescentar Material
{
	t_tup4	center;
	float	radius;
}	t_sphere;

typedef struct s_canvas
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_canvas;

typedef struct s_root
{
	void	*mlx;
	void	*win;
	t_canvas	*canvas;
}	t_root;

//CLEAN_EXIT.C
int		clean_exit(t_root *r, int exit_code);

//COLOR.C
unsigned char	float_to_shade(float color_strength);
int				tuple_to_color(t_tup4 tup4);

//TESTS.C
void	run_tests(void);

//Rays
t_ray	ray(t_tup4 origin, t_tup4 direction);

//SPHERE
void	sphere_testing();

//MAIN
void	put_pixel(t_canvas *img, int x, int y, int color);

#endif
