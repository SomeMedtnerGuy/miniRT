/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:32:47 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/06 21:42:10 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	*hit(t_intersection *xs)
{
	t_intersection	*hit;
	t_intersection	*xs_current;
	t_intersection	*current_intersection;

	hit = NULL;
	xs_current = xs;
	while (xs_current)
	{
		current_intersection = xs_current;

		if (current_intersection->t > 0 && (!hit || current_intersection->t < hit->t))
			hit = xs_current;
		xs_current = xs_current->next;
	}
	return hit;
}

t_intersection	*intersection(float value, void *object)
{
	t_intersection	*new;

	new = ft_calloc(1, sizeof(t_intersection));
	if (new == NULL)
		return (NULL);
	new->t = value;
	new->o = object;
	new->next = NULL;
	return (new);
}

t_intersection	*intersect(t_shape *shape, t_ray ray)
{
	ray = transform(ray, shape->i_transform);
	if (shape->type == SPHERE)
		return (sphere_intersect((t_sphere *)shape, ray));
	/*else if (shape->type == CYLINDER)
		return (cylinder_intersect((t_cylinder *)shape, ray));*/
	else
		return (plane_intersect((t_plane *)shape, ray));
}
