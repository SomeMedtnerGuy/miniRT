/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:00:24 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/10 18:30:04 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_material(t_shape	*shape, t_tup4 color)
{
	shape->material = material();
	shape->material->color = color;
	shape->material->diffuse = 0.7;
	shape->material->specular = 0.3;
}

void	set_transform(t_shape *shape, t_matrix4 matrix)
{
	shape->transform = matrix;
	shape->i_transform = invert_matrix4(shape->transform);
}

void	parse_sphere(char **line, t_root *r)
{
	t_tup4		center;
	float		radius;
	t_tup4		color;
	t_shape		*s;

	if(line[4])
		clean_exit(r, 1);
	center = ft_atotup(line[1], TPOINT);
	/* if(!is_coordinates(center))
		clean_exit(r, 1); */
	if(!ft_isstr_float(line[2]))
		clean_exit(r, 1);
	radius = (ft_atof(line[2]) / 2);
	color = ft_atotup(line[3], TCOLOR);
	if(!is_color(color.x, color.y, color.z))
		clean_exit(r, 1);
	s = (t_shape *)sphere();
	set_transform(s, multiply_matrix4(translation(center.x, center.y, center.z),
				scaling(radius, radius, radius)));
	set_material(s, color);
	ft_lstadd_back(&r->world->objects, ft_lstnew(s));
}

void	parse_plane(char **line, t_root *r)
{
	t_tup4		point;
	t_tup4		normal;
	t_tup4		color;
	t_shape		*p;

	if(line[4])
		clean_exit(r, 1);
	point = ft_atotup(line[1], TPOINT);
	/* if(!is_coordinates(point))
		clean_exit(r, 1); */
	color = ft_atotup(line[3], TCOLOR);
	if(!is_color(color.r, color.g, color.b))
		clean_exit(r, 1);
	normal = ft_atotup(line[2], TVECTOR);
	p = (t_shape *)plane();
	((t_plane *)p)->normal = normal;
	set_transform(p, translation(point.x, point.y, point.z));
	set_material(p, color);
	ft_lstadd_back(&r->world->objects, ft_lstnew(p));
}

void	parse_cylinder(char **line, t_root *r)
{
	t_tup4		data[3];
	float		val[2];
	t_shape		*c;

	if(line[5])
		clean_exit(r, 1);
	data[0] = ft_atotup(line[1], TPOINT);
	/* if(!is_coordinates(data[0]))
		clean_exit(r, 1); */
	data[1] = ft_atotup(line[2], TVECTOR);
	if(!is_vector(data[1].x, data[1].y, data[1].z))
		clean_exit(r, 1);
	if(!ft_isstr_float(line[2]))
		clean_exit(r, 1);
	val[0] = (ft_atof(line[2]) / 2);
	if(!ft_isstr_float(line[3]))
		clean_exit(r, 1);
	val[1] = (ft_atof(line[3]) / 2);
	data[2] = ft_atotup(line[4], TCOLOR);
	if(!is_color(data[2].r, data[2].g, data[2].b))
		clean_exit(r, 1);
	c = (t_shape *)cylinder();
	set_transform(c, translation(data[0].x, data[0].y, data[0].z));//MISSING ROTATION
	set_material(c, data[2]);
	((t_cylinder *)c)->maximum = data[0].y + val[1];
	((t_cylinder *)c)->minimum = data[0].y - val[1];
	ft_lstadd_back(&r->world->objects, ft_lstnew(c));
}
