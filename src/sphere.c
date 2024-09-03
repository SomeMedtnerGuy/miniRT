/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:21:54 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/03 14:00:32 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*sphere(void)
{
	t_sphere	*s;

	s = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	s->type = SPHERE;
	s->center = tup4(100, 100, 100, TPOINT);
	s->radius = 50;
	s->transform = identity_matrix4();
	return	(s);
}

t_intersection	*intersect(t_sphere *sphere, t_ray ray)
{
	t_tup4			sphere_to_ray;
	float			var[4];
	float			i_value[2];
	t_intersection	i[2];
	t_intersection	*xs;

	sphere_to_ray = subtract_tup4(ray.origin, sphere->center);

	var[0] = dot(ray.direction, ray.direction);
	var[1] = 2 * dot(ray.direction, sphere_to_ray);
	var[2] = dot(sphere_to_ray, sphere_to_ray) - (sphere->radius * sphere->radius);
	var[3] = var[1] * var[1] - 4 * var[0] * var[2];

	if (var[3] < 0)
		return (false);

	i_value[0] = (-var[1] - sqrt(var[3])) / (2 * var[0]);
	i_value[1] = (-var[1] + sqrt(var[3])) / (2 * var[0]);

	i[0] = intersection(i_value[0], sphere);
	i[1] = intersection(i_value[1], sphere);

	xs = intersections(4, i[0], i[1]);

	return (xs);
}

void	sphere_testing()
{
	t_ray			R;
	t_sphere		*S;
	t_intersection	*xs;
/* 	t_tup4			i_point[2]; */

	R.origin = tup4(20, 100, 100, TPOINT);
	R.direction = tup4(1, 0, 0, TVECTOR);

	S = sphere();

	xs = intersect(S, R);
	
	printf("x1 = %f\n", xs[0].t);
	printf("x2 = %f\n", xs[1].t);
	printf("x1 = %p\n", xs[0].object);
	printf("x2 = %p\n", xs[1].object);


/* 	i_point[0] = tup4((R.origin.x + i_value[0] * R.direction.x), (R.origin.y + i_value[0] * R.direction.y),
	 (R.origin.z + i_value[0] * R.direction.z), TPOINT);
	i_point[1] = tup4((R.origin.x + i_value[1] * R.direction.x), (R.origin.y + i_value[1] * R.direction.y),
	 (R.origin.z + i_value[1] * R.direction.z), TPOINT); */

	free (S);
	free(xs);
}
