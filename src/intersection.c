/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:32:47 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/03 15:33:12 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


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

	hit.t = 0.0f;
	i = 0;
	while(i < count)
	{
		if(hit.t == 0 && intersections[i].t > 0)
			hit = intersections[i];
		else if(hit.t > intersections[i].t && intersections[i].t > 0)
			hit = intersections[i];
		i++;
	}
	return (hit);
}
