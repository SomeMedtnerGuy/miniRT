/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:22:13 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/10 16:13:14 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//CHECK VALUES VERIFICATION

void	parse_ambiente(char **line, t_root *r)
{
	float	ratio;
	t_tup4	color;

	if(line[3])
		clean_exit(r, 1);

	ratio = ft_atof(line[0]);
	if(!is_float(ratio))
		clean_exit(r, 1);

	color = get_color(line[1]);
	if(!is_color(color))
		clean_exit(r, 1);

	r->world->ambiente->ratio = ratio;
	r->world->ambiente->color = color;
}

void	parse_camera(char **line, t_root *r)
{
	t_tup4	view_point;
	t_tup4	axis;
	int		fov;

	if(line[4])
		clean_exit(r, 1);

	view_point = ft_atotup(line[1]);
	if(!is_coordinates(view_point))
		clean_exit(r, 1);

	axis = ft_atotup(line[2]);
	if(!is_vector(axis))
		clean_exit(r, 1);

	fov = ft_atoi(line[3]);
	if(!(fov >= 0 && fov <= 180)) //CONVERTER PARA GRAUS
		clean_exit(r, 1);

	r->camera = camera(CANVAS_WIDTH, CANVAS_HEIGHT, (fov * (M_PI / 180)));
	r->camera->transform = view_transform(view_point, axis, vector(0, 1, 0));
}

void	parse_light(char **line, t_root *r)
{
	t_tup4	point;
	float	bright;
	t_tup4	color;

	if(line[3])
		clean_exit(r, 1);

	point = ft_atotup(line[1]);
	if(!is_coordinates(point))
		clean_exit(r, 1);

	if(!ft_isstr_float(line[2]))
		clean_exit(r, 1);
	bright = ft_atof(line[2]);

	color = get_color(line[3], bright);
	if(!is_color(color))
		clean_exit(r, 1);

//APLY BRIGHHTNESS IN GET_COLOR
	r->world->light = point_light(point, color);
}

void	parse_line(char *line, t_root *r)
{
	char	id;

	while(*line == ' ')
		*line++;
	id = get_id(*line);
	if (id == 'A')
		parse_ambiente(ft_split(line, ' '), r);
	else if (id == 'C')
		parse_camera(ft_split(line, ' '), r);
	else if (id == 'L')
		parse_light(ft_split(line, ' '), r);
	else if (id == 's')
		parse_sphere(ft_split(line, ' '), r);
	else if (id == 'p')
		parse_plane(ft_split(line, ' '), r);
	else if (id == 'c')
		parse_cylinder(ft_split(line, ' '), r);
	else
		return ;//Error
}
