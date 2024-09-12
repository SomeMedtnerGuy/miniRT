/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:00:24 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/12 15:13:06 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_material(t_shape	*shape, t_tup4 color)
{
	shape->material = material();
	shape->material.color = color;
	shape->material.diffuse = 0.9;
	shape->material.specular = 0.3;
}

void	set_transform(t_shape *shape, t_matrix4 matrix)
{
	shape->transform = matrix;
	shape->i_transform = invert_matrix4(shape->transform);
}

int	parse_sphere(char **line, t_root *r)
{
	t_tup4		center;
	float		radius;
	t_tup4		color;
	t_shape		*s;

	if (ft_arr2dsize((void **)line) != 4)
		return (1);
	center = ft_atotup(line[1], TPOINT);
	if(!ft_isstr_float(line[2]))
		return (1);
	radius = (ft_atof(line[2]) / 2);
	color = get_color(line[3]);
	if(color.w == TINVALID || center.w == TINVALID)
		return (1);
	s = (t_shape *)sphere();
	if (!s)
		return (1);
	set_transform(s, multiply_matrix4(translation(center.x, center.y, center.z),
				scaling(radius, radius, radius)));
	set_material(s, color);
	ft_lstadd_back(&r->world->objects, ft_lstnew(s));
	return (0);
}

int	parse_plane(char **line, t_root *r)
{
	t_tup4		point;
	t_tup4		normal;
	t_tup4		color;
	t_shape		*p;

	if (ft_arr2dsize((void **)line) != 4)
		return (1);
	point = ft_atotup(line[1], TPOINT);
	color = get_color(line[3]);
	normal = ft_atotup(line[2], TVECTOR);
	if(color.w == TINVALID || point.w == TINVALID
		|| normal.w == TINVALID || !tup_in_range(normal, -1, 1))
		return (1);
	normal.z = -normal.z;
	p = (t_shape *)plane();
	if (!p)
		return (1);
	set_transform(p, multiply_matrix4(translation(point.x, point.y, point.z),
			get_target_rotation(normal)));
	set_material(p, color);
	ft_lstadd_back(&r->world->objects, ft_lstnew(p));
	return (0);
}

int	parse_cylinder(char **line, t_root *r)
{
	t_tup4		data[3];
	float		val[2];
	t_shape		*c;

	if (ft_arr2dsize((void **)line) != 6)
		return (1);
	data[0] = ft_atotup(line[1], TPOINT);
	data[1] = ft_atotup(line[2], TVECTOR);
	if(!ft_isstr_float(line[3]) || !ft_isstr_float(line[4]))
		return (1);
	val[0] = (ft_atof(line[3]) / 2);
	val[1] = (ft_atof(line[4]) / 2);
	data[2] = get_color(line[5]);
	if (data[0].w == TINVALID || data[1].w == TINVALID || data[2].w == TINVALID
		|| !tup_in_range(data[1], -1, 1))
		return (1);
	c = (t_shape *)cylinder();
	if (!c)
		return (1);
	set_transform(c, multiply_matrix4(translation(data[0].x, data[0].y, data[0].z),
						get_target_rotation(normalize(data[1]))));
	set_material(c, data[2]);
	((t_cylinder *)c)->maximum = data[0].y + val[1];
	((t_cylinder *)c)->minimum = data[0].y - val[1];
	return(ft_lstadd_back(&r->world->objects, ft_lstnew(c)), 0);
}
