/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:28:26 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/10 10:23:09 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_scene(t_root *r, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if(fd < 0)
	{
		ft_putstr_fd("Error: couldn't open file\n", STDERR_FILENO);
		return (1);
	}
	if (ft_strnrcmp(file, ".rt", 3) != 0)
		ft_putstr_fd("Error: wrong file format\n", STDERR_FILENO);
	line = get_next_line(fd);
	while(line)
	{
		parse_line(line, r);
		line = get_next_line(fd);
	}
	close(fd);
}
