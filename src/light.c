/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:09:34 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/03 10:28:31 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tup4	normal_at(t_sphere *sphere, t_tup4 world_p)
{
	t_tup4	object_p;
	t_tup4	object_normal;
	t_tup4	world_normal;

	object_p = matrix4_mult_tup4(invert_matrix4(sphere->transform), world_p);
	object_normal = subtract_tup4(object_normal, point(0, 0, 0));
	world_normal = matrix4_mult_tup4(transpose_matrix4(
						invert_matrix4(sphere->transform)),
						object_normal);
	world_normal.w = TVECTOR;
	return(normalize(world_normal));
}



t_tup4	reflect(t_tup4 in, t_tup4 normal)
{
	normal = multiply_tup4(normal, 2 * dot(in, normal));
	return (subtract_tup4(in, normal));
}

t_point_light	point_light(t_tup4 position, t_tup4 intensity)
{
	t_point_light	out;

	out.position = position;
	out.intensity = intensity;
	return (out);
}

t_material	material(void)
{
	t_material	out;

	out.color = color(1, 1, 1);
	out.ambient = 0.1;
	out.diffuse = 0.9;
	out.specular = 0.9;
	out.shininess = 200.0;
	return (out);
}

t_tup4	lighting(t_light_data *data)
{
	t_tup4	effective_color;
	t_tup4	lightv;
	t_tup4	ambient;
	float	light_dot_normal;
	t_tup4	final_diffuse;
	t_tup4	final_specular;
	float	reflect_dot_eye;
	float	factor;

	effective_color = hadamard(data->material->color,
								data->light->intensity);
	lightv = normalize(subtract_tup4(data->light->position, data->point));
	ambient = multiply_tup4(effective_color, data->material->ambient);
	light_dot_normal = dot(lightv, data->normalv);
	if (light_dot_normal < 0)
	{
		final_diffuse = color(0, 0, 0);
		final_specular = color(0, 0, 0);
	}
	else
	{
		final_diffuse = multiply_tup4(effective_color,
										data->material->diffuse
										* light_dot_normal);
		reflect_dot_eye = dot(reflect(negate_tup4(lightv), data->normalv), data->eyev);
		if (reflect_dot_eye <= 0)
			final_specular = color(0, 0, 0);
		else
		{
			factor = pow(reflect_dot_eye, data->material->shininess);
			final_specular = multiply_tup4(data->light->intensity, data->material->specular * factor); 
		}
	}
	return (add_tup4(add_tup4(ambient, final_diffuse), final_specular));
}

