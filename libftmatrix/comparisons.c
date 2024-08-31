/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparisons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:40:56 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/31 17:46:19 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmatrix.h"

/*bool	ft_fcmp(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	return (false);
}*/

bool	tup4cmp(t_tup4 a, t_tup4 b)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!(fabs(a.e[i] - b.e[i]) < EPSILON))
			return (false);
	}
	return (true);
}

bool	matrix4cmp(t_matrix4 a, t_matrix4 b)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!tup4cmp(a.t[i], b.t[i]))
			return (false);
	}
	return (true);
}
