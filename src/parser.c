/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:22:13 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/11 14:22:30 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//CHECK VALUES VERIFICATION

char	get_id(char *first_arg)
{
	if (!first_arg)
		return (INVALID_OBJ);
	if (ft_strncmp(first_arg, "A", 2) == 0)
		return (AMBIENT);
	else if (ft_strncmp(first_arg, "C", 2) == 0)
		return (CAMERA);
	else if (ft_strncmp(first_arg, "L", 2) == 0)
		return (LIGHT);
	else if (ft_strncmp(first_arg, "sp", 3) == 0)
		return (SPHERE);
	else if(ft_strncmp(first_arg, "pl", 3) == 0)
		return (PLANE);
	else if(ft_strncmp(first_arg, "cy", 3) == 0)
		return (CYLINDER);
	return (INVALID_OBJ);
}

t_tup4	get_color(char *colors)
{
	char	**color_arr;
	t_tup4	out;
	int		i;
	int		shade;

	color_arr = ft_split(colors, ',');
	if (ft_arr2dsize((void **)color_arr) != 3)
		return (invalid_tup4());
	i = -1;
	while (++i < 3)
	{
		if (!ft_isstr_int(color_arr[i]))
			return (invalid_tup4());
		shade = ft_atoi(color_arr[i]);
		if (shade < 0 || shade > 255)
			return (invalid_tup4());
		out.e[i] = shade_to_float((unsigned char)shade);
	}
	out.w = TCOLOR;
	ft_matrix_free((void ***)&color_arr);
	return (out);
}

void	exit_parser(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	parse_ambient(char **line, t_root *r)
{
	float	ratio;
	t_tup4	color;

	if (ft_arr2dsize((void **)line) != 3)
		exit_parser(MISCONFIG_MSG);
	if (!ft_isstr_float(line[1]))
		exit_parser(MISCONFIG_MSG);
	ratio = ft_atof(line[1]);
	color = get_color(line[2]);
	if(color.w == TINVALID)
		exit_parser(MISCONFIG_MSG);
	r->world->ambient.ratio = ratio;
	r->world->ambient.color = color;
}

/*void	parse_camera(char **line, t_root *r)
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

	if (ft_arr2dsize(line) != 4)
		exit_with_msg(MISCONFIG_MSG, r, 1);

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
}*/

void	parse_line(char *line, t_root *r)
{
	int		id;
	char	**elements;

	elements = ft_split(line, ' ');
	if (!elements)
		return ; //Error
	id = get_id(elements[0]);
	if (id == AMBIENT)
		parse_ambient(elements, r);// perhaps return error code?
	/*else if (id == 'C')
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
		return ;//Error*/
	ft_matrix_free((void ***)&elements);
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
		parse_line(line, r);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	print_tup4(r->world->ambient.color, false);
	printf("Ratio: %f\n", r->world->ambient.ratio);
}
