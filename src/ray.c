/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:26:23 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/03 13:31:09 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray(t_tup4 origin, t_tup4 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;

	return(ray);
}

t_tup4	position(t_ray ray, float	t)
{
	t_tup4	point;

	point.x = ray.origin.x + ray.direction.x * t;
	point.y = ray.origin.y + ray.direction.y * t;
	point.z = ray.origin.z + ray.direction.z * t;
	point.w = TPOINT;

	return (point);
}

t_intersection intersection(float value,void *object)
{
	t_intersection	inter;

	inter.t = value;
	inter.object = object;
	return (inter);
}

t_intersection	*intersections(int count, ...)
{
	t_intersection	*join;
	va_list list;
	int i;

	i = 0;
	join = ft_calloc(count, sizeof(t_intersection));
	va_start(list, count);
	while(i < count)
	{
		join[i] = va_arg(list, t_intersection);
		i++;
	}

	va_end(list);

	return (join);
}
