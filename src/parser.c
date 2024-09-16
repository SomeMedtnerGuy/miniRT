/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:22:13 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/16 15:57:59 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(char **line, t_root *r)
{
	float	ratio;
	t_tup4	color;

	if (ft_arr2dsize((void **)line) != 3)
		return (1);
	if (!ft_isstr_float(line[1]))
		return (1);
	ratio = ft_atof(line[1]);
	if (ratio < 0 || ratio > 1)
		return (1);
	color = get_color(line[2]);
	if (color.w == TINVALID)
		return (1);
	r->world->ambient.ratio = ratio;
	r->world->ambient.color = color;
	return (0);
}

int	parse_camera(char **line, t_root *r)
{
	t_tup4	view_point;
	t_tup4	axis;
	int		fov;
	t_tup4	upv;

	if (ft_arr2dsize((void **)line) != 4)
		return (1);
	view_point = ft_atotup(line[1], TPOINT);
	axis = ft_atotup(line[2], TVECTOR);
	if (view_point.w == TINVALID || axis.w == TINVALID
		|| !ft_isstr_int(line[3]))
		return (1);
	fov = ft_atoi(line[3]);
	if (!(fov >= 0 && fov <= 180) || !tup_in_range(axis, -1, 1))
		return (1);
	axis = normalize(axis);
	r->world->camera = camera(CANVAS_WIDTH, CANVAS_HEIGHT,
			(fov * (M_PI / 180)));
	upv = vector(0, 1, 0);
	if (tup4cmp(axis, vector(0, 1, 0))
		|| tup4cmp(axis, vector(0, -1, 0)))
		upv = vector(0, 0, 1);
	r->world->camera->transform = view_transform(view_point, axis,
			upv);
	return (0);
}

int	parse_light(char **line, t_root *r)
{
	t_tup4	point;
	float	bright;
	t_tup4	color;

	if (ft_arr2dsize((void **)line) != 4)
		return (1);
	point = ft_atotup(line[1], TPOINT);
	if (point.w == TINVALID || !ft_isstr_float(line[2]))
		return (1);
	bright = ft_atof(line[2]);
	color = get_color(line[3]);
	if (color.w == TINVALID || !(bright >= 0 && bright <= 1))
		return (1);
	color = multiply_tup4(color, bright);
	r->world->light = point_light(point, color);
	return (0);
}

int	parse_line(char *line, t_root *r)
{
	int		id;
	char	**elements;

	elements = ft_split(line, ' ');
	if (!elements)
		return (1);
	id = get_id(elements[0]);
	id = is_duplicate(id);
	if (id == AMBIENT)
		id = parse_ambient(elements, r);
	else if (id == CAMERA)
		id = parse_camera(elements, r);
	else if (id == LIGHT)
		id = parse_light(elements, r);
	else if (id == SPHERE)
		id = parse_sphere(elements, r);
	else if (id == PLANE)
		id = parse_plane(elements, r);
	else if (id == CYLINDER)
		id = parse_cylinder(elements, r);
	else
		id = 1;
	ft_matrix_free((void ***)&elements);
	return (id);
}

void	parse_config_file(char *filename, t_root *r)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(FILE_ERROR_MSG, 2);
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (*line && parse_line(line, r) != 0)
		{
			free_world(r->world);
			exit_parser(line, fd, MISCONFIG_MSG);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (!r->world->camera)
	{
		free_world(r->world);
		exit_parser(line, fd, MISCONFIG_MSG);
	}
	close(fd);
}
