/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:09:34 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/05 19:16:44 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tup4	normal_at(t_sphere *sphere, t_tup4 world_p)
{
	t_tup4	object_p;
	t_tup4	object_normal;
	t_tup4	world_normal;

	object_p = matrix4_mult_tup4(invert_matrix4(sphere->transform), world_p);
	object_normal = subtract_tup4(object_p, point(0, 0, 0));
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

t_point_light	*point_light(t_tup4 position, t_tup4 intensity)
{
	t_point_light	*out;

	out = (t_point_light *)ft_calloc(1, sizeof(t_point_light));
	out->position = position;
	out->intensity = intensity;
	return (out);
}

t_material	*material(void)
{
	t_material	*out;

	out = ft_calloc(1, sizeof(t_material));
	out->color = color(1, 1, 1);
	out->ambient = 0.1;
	out->diffuse = 0.9;
	out->specular = 0.9;
	out->shininess = 200.0;
	return (out);
}

static void	direct_lighting(t_light_data *data, t_tup4 effective_color,
							float light_dot_normal)
{
	float	factor;
	float	reflect_dot_eye;

	data->final_diffuse = multiply_tup4(effective_color,
									data->material->diffuse
									* light_dot_normal);
	reflect_dot_eye = dot(reflect(negate_tup4(data->lightv), data->normalv), data->eyev);
	if (reflect_dot_eye <= 0)
		data->final_specular = color(0, 0, 0);
	else
	{
		factor = pow(reflect_dot_eye, data->material->shininess);
		data->final_specular = multiply_tup4(data->light->intensity, data->material->specular * factor); 
	}
}

t_tup4	lighting(t_light_data *data)
{
	t_tup4	effective_color;
	float	light_dot_normal;

	effective_color = hadamard(data->material->color,
								data->light->intensity);
	data->lightv = normalize(subtract_tup4(data->light->position, data->point));
	data->final_ambient = multiply_tup4(effective_color, data->material->ambient);
	light_dot_normal = dot(data->lightv, data->normalv);
	if (light_dot_normal < 0)
	{
		data->final_diffuse = color(0, 0, 0);
		data->final_specular = color(0, 0, 0);
	}
	else
		direct_lighting(data, effective_color, light_dot_normal);
	return (add_tup4(add_tup4(data->final_ambient, data->final_diffuse), data->final_specular));
}

