/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:22:13 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/10 19:37:07 by joamonte         ###   ########.fr       */
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

	if(!ft_isstr_float(line[0]))
		clean_exit(r, 1);
	ratio = ft_atof(line[0]);
	color = ft_atotup(line[1], TCOLOR);
	if(!is_color(color.r, color.g, color.b))
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
	//COORDINATES VERIFICATION
	view_point = ft_atotup(line[1], TPOINT);
	axis = ft_atotup(line[2], TVECTOR);
	if(!is_vector(axis.x, axis.y, axis.z))
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
	ft_rm_char(line[1], ' ');
	point = ft_atotup(line[1], TPOINT);
	/* if(!is_coordinates(point))
		clean_exit(r, 1); */
	if(!ft_isstr_float(line[2]))
		clean_exit(r, 1);
	bright = ft_atof(line[2]);
	color = ft_atotup(line[3], 1);
	if(!is_color(color.r, color.g, color.b))
		clean_exit(r, 1);
	color = multiply_tup4(color, bright);
	r->world->light = point_light(point, color);
}

void	free_split(char **split)
{
	int i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	parse_line(char *line, t_root *r)
{
	char	id;
	char	**split_line;

	split_line = ft_split(line, ' ');
	id = get_id(line);
	if (id == 'A')
		parse_ambiente(split_line, r);
	else if (id == 'C')
		parse_camera(split_line, r);
	else if (id == 'L')
		parse_light(split_line, r);
	else if (id == 's')
		parse_sphere(split_line, r);
	else if (id == 'p')
		parse_plane(split_line, r);
	else if (id == 'c')
		parse_cylinder(split_line, r);
	else
	{
		free(split_line);
		return ;//Error
	}
	free_split(split_line);
}
