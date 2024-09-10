/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:35:42 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/10 19:04:21 by ndo-vale         ###   ########.fr       */
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

typedef struct s_ambiente
{
	float	ratio;
	t_tup4	color;
}	t_ambiente;

typedef struct s_light_data
{
	t_material		*material;
	t_point_light	*light;
	t_ambiente		*ambiente;
	bool			in_shadow;
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

typedef enum obj_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_obj_type;

typedef struct s_shape
{
	t_obj_type	type;
	t_material	*material;
	t_matrix4	transform;
	t_matrix4	i_transform;
}	t_shape;

typedef struct s_intersection
{
	float					t;
	t_shape					*o;
	struct s_intersection	*next;
}	t_intersection;

typedef struct s_world
{
	t_point_light	*light;
	t_ambiente		*ambiente;
	t_list			*objects;
	t_intersection	*xs;
}	t_world;

typedef struct s_sphere
{
	t_obj_type	type;
	t_material	*material;
	t_matrix4	transform;
	t_matrix4	i_transform;
	t_tup4		center;
	float		radius;
}	t_sphere;

typedef struct s_plane
{
	t_obj_type	type;
	t_material	*material;
	t_matrix4	transform;
	t_matrix4	i_transform;
	t_tup4		normal;
}	t_plane;

typedef struct s_cylinder
{
	t_obj_type	type;
	t_material	*material;
	t_matrix4	transform;
	t_matrix4	i_transform;
	float		minimum;
	float		maximum;
	bool		closed;
}	t_cylinder;

typedef struct s_comps
{
	float	t;
	t_shape	*object;
	t_tup4	point;
	t_tup4	eyev;
	t_tup4	normalv;
	bool	inside;
	t_tup4	over_point;
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
	t_world		*world;
	t_camera	*camera;
}	t_root;

//MAIN.C
t_point_light	*point_light(t_tup4 position, t_tup4 intensity);
t_material		*material(void);

//CLEAN_EXIT.C
int				clean_exit(t_root *r, int exit_code);

//COLOR.C
unsigned char	float_to_shade(float color_strength);
int				tuple_to_color(t_tup4 tup4);
t_tup4			color_at(t_world *w, t_ray r);
float			shade_to_float(unsigned char shade);

//LIGHT
t_tup4			reflect(t_tup4 in, t_tup4 normal);
t_tup4			lighting(t_light_data *data);
bool			is_shadowed(t_world *w, t_tup4 p);
t_tup4			shade_hit(t_world *w, t_comps comps);

//RAY.C
t_ray			ray(t_tup4 origin, t_tup4 direction);
t_tup4			position(t_ray ray, float t);
t_ray			transform(t_ray ray, t_matrix4 matrix);

//LST_UTILS.C
int				int_size(t_intersection *lst);
t_intersection	*intlast(t_intersection *lst);
int				int_add_back(t_intersection **lst, t_intersection *new);
void			intclear(t_intersection **lst);
void			int_add_front(t_intersection **lst, t_intersection *new);

//LSTADD_XS_SORTED.C
void			lstadd_xs_sorted(t_intersection **lst, t_intersection *new);

//GET_TARGET_ROTATION.C
t_matrix4	get_target_rotation(t_tup4 target_y_vec);

//INTERSECTION.C
t_intersection	*intersection(float value, void *object);
t_intersection	*hit(t_intersection *xs);
t_intersection	*intersect(t_shape *shape, t_ray ray);
t_tup4			normal_at(t_shape *shape, t_tup4 point);

//SPHERE.C
t_sphere		*sphere(void);
void			set_transform(t_shape *shape, t_matrix4 matrix);
t_intersection	*sphere_intersect(t_sphere *sphere, t_ray ray);
t_tup4			sphere_normal_at(t_sphere *sphere, t_tup4 object_p);

//PLANE.C
t_plane			*plane(void);
t_intersection	*plane_intersect(t_plane *plane, t_ray ray);

//CYLINDER.C
t_cylinder		*cylinder(void);
t_intersection	*cylinder_intersect(t_cylinder *cylinder, t_ray ray);
t_tup4			cylinder_normal_at(t_cylinder *c, t_tup4 world_p);
void			intersect_caps(t_cylinder *cyl, t_ray ray, t_intersection **xs);

//CAMERA.C
t_matrix4		view_transform(t_tup4 from, t_tup4 to, t_tup4 up);
t_camera		*camera(float hsize, float vsize, float field_of_view);
t_ray			ray_for_pixel(t_camera *camera, float px, float py);

//WORLD.C
t_world			*world(void);
t_intersection	*intersect_world(t_world *w, t_ray r);
t_comps			prepare_computations(t_intersection *intersection, t_ray ray);
void			render(t_canvas *canvas, t_camera *camera, t_world *world);

#endif
