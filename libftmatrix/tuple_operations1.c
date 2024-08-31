/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:46:06 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/31 14:12:25 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmatrix.h"

t_tup4	add_tup4(t_tup4 a, t_tup4 b)
{
	return (tup4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
}

t_tup4	subtract_tup4(t_tup4 a, t_tup4 b)
{
	return (tup4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w));
}

t_tup4	negate_tup4(t_tup4 a)
{
	return (tup4(-a.x, -a.y, -a.z, -a.w));
}

t_tup4	multiply_tup4(t_tup4 a, float s)
{
	return (tup4(a.x * s, a.y * s, a.z * s, a.w * s));
}

t_tup4	divide_tup4(t_tup4 a, float s)
{
	if (are_floats_equal(s, 0))
		return (tup4(0, 0, 0, 0));
	return (tup4(a.x / s, a.y / s, a.z / s, a.w / s));
}
