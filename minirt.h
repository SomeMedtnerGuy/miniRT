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

typedef struct s_material
{
	t_tup4	color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}	t_material;

typedef struct s_point_light
{
	t_tup4	intensity;
	t_tup4	position;
}	t_point_light;

typedef struct s_light_data
{
	t_material		*material;
	t_point_light	*light;
	t_tup4			point;
	t_tup4			eyev;
	t_tup4			normalv;
}	t_light_data;

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

//LIGHT
/*t_tup4	normal_at(t_sphere sphere, t_tup4 p);*/
t_tup4	reflect(t_tup4 in, t_tup4 normal);
t_point_light	point_light(t_tup4 position, t_tup4 intensity);
t_material	material(void);

//TESTS.C
void	run_tests(void);

//Rays
t_ray	ray(t_tup4 origin, t_tup4 direction);

//SPHERE
void	sphere_testing();

//MAIN
void	put_pixel(t_canvas *img, int x, int y, int color);

#endif
