/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:22:13 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/10 10:49:31 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	get_id(char *line)
{
	char	id;

	if (line[0] == 'A' || line[0] == 'C' || line[0] == 'L')
		id = line[0];
	else if ((line[0] == 's' && line[1] == 'p')
			|| (line[0] == 'p' && line[1] == 'l')
			|| (line[0] == 'c' && line[1] == 'y'))
		id = line[0];
	else
		return('\0');
	return(id);
}

void	parse_line(char *line, t_root *r)
{
	char	id;

	while(*line == ' ')
		line++;
	id = get_id(*line);
	if (id == 'A')
		parse_ambiente(line, r);
	else if (id == 'C')
		parse_camera(line, r);
	else if (id == 'L')
		parse_light(line, r);
	else if (id == 's')
		parse_sphere(line, r);
	else if (id == 'p')
		parse_plane(line, r);
	else if (id == 'c')
		parse_cylinder(line, r);
	else
		//Error
}
