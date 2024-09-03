/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:21:54 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/03 17:38:39 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*sphere(void)
{
	t_sphere	*s;

	s = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	s->type = SPHERE;
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
	t_intersection	i[2];
	t_intersection	*xs;

	ray = transform(ray, sphere->transform);

	sphere_to_ray = subtract_tup4(ray.origin, sphere->center);

	var[0] = dot(ray.direction, ray.direction);
	var[1] = 2 * dot(ray.direction, sphere_to_ray);
	var[2] = dot(sphere_to_ray, sphere_to_ray) - (sphere->radius * sphere->radius);
	var[3] = var[1] * var[1] - 4 * var[0] * var[2];

	printf("var[0] value: %f\n", var[0]);
	printf("var[1] value: %f\n", var[1]);
	printf("var[2] value: %f\n", var[2]);
	printf("var[3] value: %f\n", var[3]);

	if (var[3] < 0)
		return (NULL);

	i_value[0] = (-var[1] - sqrt(var[3])) / (2 * var[0]);
	i_value[1] = (-var[1] + sqrt(var[3])) / (2 * var[0]);

	i[0] = intersection(i_value[0], sphere);
	i[1] = intersection(i_value[1], sphere);

	xs = intersections(2, i[0], i[1]);
	return (xs);
}

void	set_transform(t_sphere *sphere, t_matrix4 matrix)
{
	sphere->transform.t[0] = matrix.t[0];
	sphere->transform.t[1] = matrix.t[1];
	sphere->transform.t[2] = matrix.t[2];
	sphere->transform.t[3] = matrix.t[3];
}

void	sphere_testing()
{
	t_ray			R;
	t_sphere		*S;
	t_intersection	*xs;
/* 	t_tup4			i_point[2]; */
	//t_intersection	i;
	t_matrix4	scaling;

	R.origin = tup4(1, 2, 3, TPOINT);
	R.direction = tup4(0, 1, 0, TVECTOR);

	S = sphere();

	scaling = matrix4(tup4(2, 0, 0, 0), tup4(0, 3, 0, 0),
			tup4(0, 0, 4, 0), tup4(0, 0, 0, 1));

	set_transform(S, scaling);

	xs = intersect(S, R);

	//i = hit(xs, sizeof(*xs) / sizeof(xs[0]));
	if(xs)
	{
		printf("X1.t %f\n", xs[0].t);
		printf("X2.t %f\n", xs[1].t);
	}

/* 	i_point[0] = tup4((R.origin.x + i_value[0] * R.direction.x), (R.origin.y + i_value[0] * R.direction.y),
	 (R.origin.z + i_value[0] * R.direction.z), TPOINT);
	i_point[1] = tup4((R.origin.x + i_value[1] * R.direction.x), (R.origin.y + i_value[1] * R.direction.y),
	 (R.origin.z + i_value[1] * R.direction.z), TPOINT); */

	free (S);
	free(xs);
}
