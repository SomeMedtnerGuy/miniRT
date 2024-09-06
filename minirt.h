/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:35:42 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/06 17:50:49 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdarg.h>
# include "mlx_linux/mlx_int.h"
# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include "libftmatrix/libftmatrix.h"

# define CANVAS_WIDTH 600
# define CANVAS_HEIGHT 300

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
	t_tup4			lightv;
	t_tup4			normalv;
	t_tup4			final_ambient;
	t_tup4			final_diffuse;
	t_tup4			final_specular;
}	t_light_data;

typedef struct s_ray
{
	t_tup4	origin;
	t_tup4	direction;
}	t_ray;

typedef struct	s_intersection
{
	float					t;
	void					*o;
	struct s_intersection	*next;
}	t_intersection;

typedef struct s_world
{
	t_point_light	*light;
	t_list	*objects;
	t_intersection	*xs;
}	t_world;

typedef enum	obj_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_obj_type;

typedef struct s_object
{
	t_obj_type	type;
	t_material	*material;
	t_matrix4	transform;
	t_matrix4	i_transform;
}	t_object;

typedef struct s_sphere
{
	t_obj_type	type;
	t_material	*material;
	t_matrix4	transform;
	t_matrix4	i_transform;
	t_tup4		center;
	float		radius;
}	t_sphere;

/*typedef struct	s_intersection
{
	float		t;
	void		*object; //Perhaps change this type to t_object?
	struct s_intersection	*next;
}	t_intersection;*/

typedef struct s_comps
{
	float	t;
	void	*object;
	t_tup4	point;
	t_tup4	eyev;
	t_tup4	normalv;
	bool	inside;
}	t_comps;

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

typedef struct s_camera
{
	float		hsize;
	float		vsize;
	float		field_of_view;
	float		half_width;
	float		half_height;
	float		pixel_size;
	t_matrix4	transform;

}	t_camera;

typedef struct s_root
{
	void		*mlx;
	void		*win;
	t_canvas	*canvas;
}	t_root;

//CLEAN_EXIT.C
int				clean_exit(t_root *r, int exit_code);

//COLOR.C
unsigned char	float_to_shade(float color_strength);
int				tuple_to_color(t_tup4 tup4);

//LIGHT
t_tup4	normal_at(t_sphere *sphere, t_tup4 p);
t_tup4	reflect(t_tup4 in, t_tup4 normal);
t_point_light	*point_light(t_tup4 position, t_tup4 intensity);
t_material	*material(void);
t_tup4	lighting(t_light_data *data);
/*
t_tup4			normal_at(t_sphere *sphere, t_tup4 p);
t_tup4			reflect(t_tup4 in, t_tup4 normal);
t_point_light	point_light(t_tup4 position, t_tup4 intensity); //CHECK IF POINTER IS NEEDED
t_material		material(void);                                 //CHECK IF POINTER IS NEEDED
t_tup4			lighting(t_light_data *data);*/

//TESTS.C
void			run_tests(void);

//RAY.C
t_ray			ray(t_tup4 origin, t_tup4 direction);
t_tup4			position(t_ray ray, float	t);
t_ray			transform(t_ray ray, t_matrix4 matrix);

//LST_UTILS.C
int				int_size(t_intersection *lst);
t_intersection	*intlast(t_intersection *lst);
int				int_add_back(t_intersection **lst, t_intersection *new);
void			intclear(t_intersection **lst);
void			int_front(t_intersection **lst, t_intersection *new);

//INTERSECTION.C
t_intersection	*intersection(float value, void *object);
t_intersection	*hit(t_intersection *xs);

//SPHERE.C
t_sphere		*sphere(void);
void			set_transform(t_sphere *sphere, t_matrix4 matrix);
t_intersection	*intersect(t_sphere *sphere, t_ray ray);

//WORLD.C
t_world			*world(void);
t_world			*default_world(void);
t_intersection	*intersect_world(t_world *w, t_ray r);
t_comps			prepare_computations(t_intersection *intersection, t_ray ray);
t_tup4			shade_hit(t_world *w, t_comps comps);
t_tup4			color_at(t_world *w, t_ray r);
t_matrix4		view_transform(t_tup4 from, t_tup4 to, t_tup4 up);
t_camera		*camera(float hsize, float vsize, float field_of_view);
t_ray			ray_for_pixel(t_camera *camera, float px, float py);
void			render(t_canvas *canvas, t_camera *camera, t_world *world);

//MAIN
void			put_pixel(t_canvas *img, int x, int y, int color);

#endif
