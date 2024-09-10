/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:34:22 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/10 13:30:50 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* void ft_rm_char(char *str, char c)
{
	char *prt1 = str, *prt2 = str;

	while (*prt1 != '\0')
	{
		if (*prt1 != c)
		{
			*prt2 = *prt1;
			prt2++;
		}
		prt1++;
	}
	*prt2 = '\0';
} */

bool	ft_str_isfloat(char *str)
{
	int		i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (!(ft_isdigit(str[i]) == true || str[i] == '-' || str[i] == '+' ||
							str[i] == '.'))
			return (false);
		i++;
	}
	return (true);
}

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
