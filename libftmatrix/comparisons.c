/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparisons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:40:56 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/31 14:33:39 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmatrix.h"

bool	are_floats_equal(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (true);
	return (false);
}

bool	are_tup4_equal(t_tup4 a, t_tup4 b)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (a.e[i] != b.e[i])
			return (false);
	}
	return (true);
}

bool	are_matrix4_equal(t_matrix4 a, t_matrix4 b)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!are_tup4_equal(a.t[i], b.t[i]))
			return (false);
	}
	return (true);
}
