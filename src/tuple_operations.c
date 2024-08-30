/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:46:06 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/30 12:32:55 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_tup4	scale_tup4(t_tup4 a, char operation, float s)
{
	if (ft_isequal(s, 0))
		return (tup4(0, 0, 0, 0));
	else if (operation == MULTIPLY)
		return (tup4(a.x * s, a.y * s, a.z * s, a.w * s));
	else //(operation == DIVIDE)
		return (tup4(a.x / s, a.y / s, a.z / s, a.w / s));
}

float	magnitude(t_tup4 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w));
}

t_tup4	normalize(t_tup4 a)
{
	return (scale_tup4(a, DIVIDE, magnitude(a)));
}

float	dot(t_tup4 a, t_tup4 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

t_tup4	cross(t_tup4 a, t_tup4 b)
{
	return (tup4(a.y * b.z - a.z - b.y,
			a.z * b.x - a.x - b.z,
			a.x * b.y - a.y * b.x, TVECTOR));
}

t_tup4	hadamard(t_tup4 a, t_tup4 b)
{
	return (tup4(a.x * b.x, a.y * b.y, a.z * b.z, TCOLOR));
}