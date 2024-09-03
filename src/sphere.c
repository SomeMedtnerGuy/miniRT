/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:21:54 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/03 10:59:48 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*sphere(void)
{
	t_sphere	*s;

	s = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	s->center = tup4(100, 100, 100, TPOINT);
	s->radius = 50;
	s->transform = identity_matrix4();
	return	(s);
}

bool	intersect(t_sphere *sphere, t_ray ray, float *t1, float *t2)
{
	t_tup4	sphere_to_ray;
	float	a, b, c, discriminant;

	sphere_to_ray = subtract_tup4(ray.origin, sphere->center);

	a = dot(ray.direction, ray.direction);
	printf("A: %f\n", a);

	b = 2 * dot(ray.direction, sphere_to_ray);
	printf("B: %f\n", b);

	c = dot(sphere_to_ray, sphere_to_ray) - (sphere->radius * sphere->radius);
	printf("C: %f\n", c);

	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (false);

	*t1 = (-b - sqrt(discriminant)) / (2 * a);
	*t2 = (-b + sqrt(discriminant)) / (2 * a);

	return (true);
}

void	sphere_testing(t_root r)
{
	t_ray		A;
	t_sphere	*S;
	float	intersection[2];
	t_tup4	int_points[2];
	bool	check;

	A.origin = tup4(20, 100, 100, TPOINT);
	A.direction = tup4(1, 0, 0, TVECTOR);

	S = sphere();

	check = intersect(S, A, &intersection[0], &intersection[1]);

	printf("Point 1 Value: %f\n", intersection[0]);
	printf("Point 2 Value: %f\n", intersection[1]);

	int_points[0] = tup4((A.origin.x + intersection[0] * A.direction.x), (A.origin.y + intersection[0] * A.direction.y),
	 (A.origin.z + intersection[0] * A.direction.z), TPOINT);

	int_points[1] = tup4((A.origin.x + intersection[1] * A.direction.x), (A.origin.y + intersection[1] * A.direction.y),
	 (A.origin.z + intersection[1] * A.direction.z), TPOINT);

	printf("Point 1 X Coordinate : %f\n", int_points[0].x);
	printf("Point 1 Y Coordinate : %f\n", int_points[0].y);
	printf("Point 1 Z Coordinate : %f\n", int_points[0].z);

	printf("Point 2 X Coordinate : %f\n", int_points[1].x);
	printf("Point 2 Y Coordinate : %f\n", int_points[1].y);
	printf("Point 2 Z Coordinate : %f\n", int_points[1].z);

	printf("Your boolean variable is: %s\n", check ? "true" : "false");

	if(check)
	{
		printf("It intersects\n");
		put_pixel(r.canvas, A.origin.x, A.origin.y, 0xffffff);
		put_pixel(r.canvas, S->center.x, S->center.y, 0xff0000);
		put_pixel(r.canvas, int_points[0].x, int_points[0].y, 0x00ff00);
		put_pixel(r.canvas, int_points[1].x, int_points[1].y, 0x00ff00);
	}
	else
		printf("It doesnt intersect\n");
}
