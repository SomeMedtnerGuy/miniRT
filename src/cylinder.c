/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:48:01 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/06 21:54:55 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*cylinder(void)
{
	t_cylinder	*p;

	p = (t_plane *)ft_calloc(1, sizeof(t_plane));
	p->type = PLANE;
	p->transform = identity_matrix4();
	p->i_transform = identity_matrix4();
	p->material = material();
	return	(p);
}

t_intersection	*cylinder_intersect(t_plane *plane, t_ray ray)
{
	float			i_value;
	t_intersection	*xs;

	if (ray.direction.y < EPSILON)
		return (NULL);
	i_value = -ray.origin.y / ray.direction.y;
	xs = NULL;
	int_add_back(&xs, intersection(i_value, plane));
	return (xs);
}