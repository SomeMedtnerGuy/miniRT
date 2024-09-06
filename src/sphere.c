/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:21:54 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/06 16:45:03 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*sphere(void)
{
	t_sphere	*s;

	s = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	s->type = SPHERE;
	s->material = material();
	s->center = tup4(0, 0, 0, TPOINT);
	s->radius = 1;
	s->transform = identity_matrix4();
	return	(s);
}

t_intersection	*intersect(t_sphere *sphere, t_ray ray)
{
	t_tup4			sphere_to_ray;
	float			var[4];
	float			i_value[2];
	t_intersection	*xs;

	ray = transform(ray, invert_matrix4(sphere->transform));
	sphere_to_ray = subtract_tup4(ray.origin, sphere->center);
	var[0] = dot(ray.direction, ray.direction);
	var[1] = 2 * dot(ray.direction, sphere_to_ray);
	var[2] = dot(sphere_to_ray, sphere_to_ray) - (sphere->radius * sphere->radius);
	var[3] = var[1] * var[1] - 4 * var[0] * var[2];
	if (var[3] < 0)
		return (NULL);
	i_value[0] = (-var[1] - sqrt(var[3])) / (2 * var[0]);
	i_value[1] = (-var[1] + sqrt(var[3])) / (2 * var[0]);
	xs = NULL;
	
	int_add_back(&xs, intersection(i_value[0], sphere));
	int_add_back(&xs, intersection(i_value[1], sphere));

	return (xs);
}

void	set_transform(t_sphere *sphere, t_matrix4 matrix)
{
	sphere->transform.t[0] = matrix.t[0];
	sphere->transform.t[1] = matrix.t[1];
	sphere->transform.t[2] = matrix.t[2];
	sphere->transform.t[3] = matrix.t[3];
	//sphere->itransform = invert_matrix4(sphere->transform);
}
