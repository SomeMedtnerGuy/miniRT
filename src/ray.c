/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:26:23 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/03 15:27:36 by joamonte         ###   ########.fr       */
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

t_intersection	hit(t_intersection *intersections, int count)
{
	int	i;
	t_intersection	hit;

	hit.t = -1.0f;
	i = 0;
	while(i < count)
	{
		if(hit.t < 0 && intersections[i].t > 0)
			hit = intersections[i];
		else if(hit.t > intersections[i].t && intersections[i].t > 0)
			hit = intersections[i];
		i++;
	}
	return (hit);
}
