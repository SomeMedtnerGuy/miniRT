/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:35:42 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/30 15:14:37 by joamonte         ###   ########.fr       */
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

# define EPSILON 0.00001
# define TVECTOR 0.0
# define TPOINT 1.0
# define TCOLOR 2.0
# define CANVAS_WIDTH 900
# define CANVAS_HEIGHT 500

# define WINDOW_TITLE "miniRT"

# define PLUS '+'
# define MINUS '-'
# define MULTIPLY '*'
# define DIVIDE '/'
# define DOT '.'
# define CROSS 'x'

typedef struct s_tup2
{
	float	e[2];
}	t_tup2;

typedef struct s_tup3
{
	float	e[3];
}	t_tup3;

typedef union u_tup4
{
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
	struct
	{
		float	r;
		float	g;
		float	b;
		float	a;
	};
	float	e[4];
}	t_tup4;

typedef union u_matrix2
{
	t_tup2	t[2];
	float	e[2][2];
}	t_matrix2;

typedef union u_matrix3
{
	t_tup3	t[3];
	float	e[3][3];
}	t_matrix3;

typedef union u_matrix4
{
	t_tup4	t[4];
	float	e[4][4];
}	t_matrix4;


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

//HELPERS.C
bool	ft_isequal(float a, float b);

//TUPLE_FACTORY.C
t_tup2  tup2(float x, float y);
t_tup3  tup3(float x, float y, float z);
t_tup4  tup4(float x, float y, float z, float w);
t_tup4  point(float x, float y, float z);
t_tup4  vector(float x, float y, float z);
t_tup4  color(float x, float y, float z);

//TUPLE_OPERATIONS.C
bool	are_tup4_equal(t_tup4 a, t_tup4 b);
t_tup4	add_tup4(t_tup4 a, t_tup4 b);
t_tup4	subtract_tup4(t_tup4 a, t_tup4 b);
t_tup4	negate_tup4(t_tup4 a);
t_tup4	scale_tup4(t_tup4 a, char operation, float s);
float	magnitude(t_tup4 a);
t_tup4	normalize(t_tup4 a);
float	dot(t_tup4 a, t_tup4 b);
t_tup4	cross(t_tup4 a, t_tup4 b);
t_tup4	hadamard(t_tup4 a, t_tup4 b);

//MATRIX_FACTORY.C
t_matrix2	matrix2(t_tup2 x, t_tup2 y);
t_matrix3	matrix3(t_tup3 x, t_tup3 y, t_tup3 z);
t_matrix4	matrix4(t_tup4 x, t_tup4 y, t_tup4 z, t_tup4 w);
t_matrix4	id_matrix4(void);

//MATRIX_OPERATIONS.C
bool    are_matrix4_equal(t_matrix4 a, t_matrix4 b);
t_tup4	get_column_from_matrix4(t_matrix4 a, int i);
t_matrix4	transpose_matrix4(t_matrix4 a);
t_matrix4   multiply_matrix(t_matrix4 a, t_matrix4 b);

#endif
