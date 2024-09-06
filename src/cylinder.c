/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:48:01 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/06 22:44:53 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*cylinder(void)
{
	t_cylinder	*p;

	p = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	p->type = CYLINDER;
	p->transform = identity_matrix4();
	p->i_transform = identity_matrix4();
	p->material = material();
	return	(p);
}

t_intersection	*cylinder_intersect(t_cylinder *cylinder, t_ray ray)
{
	float			var[4];
	float			i_value[2];
	t_intersection	*xs;

	var[0] = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	if (fabsf(var[0]) < EPSILON)
		return (NULL);
	var[1] = 2 * ray.origin.x * ray.direction.x
			+ 2 * ray.origin.z * ray.direction.z;
	var[2] = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1;
	var[3] = var[1] * var[1] - 4 * var[0] * var[2];
	if (var[3] < 0)
		return (NULL);
	i_value[0] = (-var[1] - sqrt(var[3])) / (2 * var[0]);
	i_value[1] = (-var[1] + sqrt(var[3])) / (2 * var[0]);
	xs = NULL;
	
	int_add_back(&xs, intersection(i_value[0], cylinder));
	int_add_back(&xs, intersection(i_value[1], cylinder));

	return (xs);
}

t_tup4	cylinder_normal_at(t_cylinder *c, t_tup4 world_p)
{
	(void)c;
	return (vector(world_p.x, 0, world_p.z));
}