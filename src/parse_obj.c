/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:00:24 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/11 17:30:28 by joamonte         ###   ########.fr       */
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

	printf("sphere\n");
	if (ft_arr2dsize((void **)line) != 4)
		exit_parser(MISCONFIG_MSG);

	center = ft_atotup(line[1], TPOINT);
	//COORDINATES VERIFICATION

	if(!ft_isstr_float(line[2]))
		exit_parser(MISCONFIG_MSG);
	radius = (ft_atof(line[2]) / 2);
	color = get_color(line[3]);
	if(color.w == TINVALID)
		exit_parser(MISCONFIG_MSG);
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

	printf("plane\n");
	if (ft_arr2dsize((void **)line) != 4)
		exit_parser(MISCONFIG_MSG);

	point = ft_atotup(line[1], TPOINT);
	//COORDINATES VERIFICATION
	
	color = get_color(line[3]);
	if(color.w == TINVALID)
		exit_parser(MISCONFIG_MSG);
	normal = ft_atotup(line[2], TVECTOR);
	if(!is_vector(normal.x, normal.y, normal.z))
		exit_parser(MISCONFIG_MSG);
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

	printf("cylinder\n");
	if (ft_arr2dsize((void **)line) != 5)
		exit_parser(MISCONFIG_MSG);
	data[0] = ft_atotup(line[1], TPOINT);
	
	data[1] = ft_atotup(line[2], TVECTOR);
	if(!is_vector(data[1].x, data[1].y, data[1].z))
		exit_parser(MISCONFIG_MSG);
		
	if(!ft_isstr_float(line[2]))
		exit_parser(MISCONFIG_MSG);
	val[0] = (ft_atof(line[2]) / 2);
	
	if(!ft_isstr_float(line[3]))
		exit_parser(MISCONFIG_MSG);
	val[1] = (ft_atof(line[3]) / 2);
	
	data[2] = get_color(line[4]);
	if(data[2].w == TINVALID)
		exit_parser(MISCONFIG_MSG);

	c = (t_shape *)cylinder();
	set_transform(c, translation(data[0].x, data[0].y, data[0].z));//MISSING ROTATION
	set_material(c, data[2]);
	((t_cylinder *)c)->maximum = data[0].y + val[1];
	((t_cylinder *)c)->minimum = data[0].y - val[1];
	ft_lstadd_back(&r->world->objects, ft_lstnew(c));
}
