/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:21:44 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/10 15:08:42 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4	view_transform(t_tup4 from, t_tup4 to, t_tup4 up)
{
	//t_tup4		forward;
	t_tup4		left;
	t_tup4		true_up;
	t_matrix4	orientation;

	//forward = normalize(subtract_tup4(to, from));
	left = cross(to, normalize(up));
	true_up = cross(left, to);
	orientation = matrix4(
			tup4(left.x, left.y, left.z, 0),
			tup4(true_up.x, true_up.y, true_up.z, 0),
			tup4(-to.x, -to.y, -to.z, 0),
			tup4(0, 0, 0, 1));
	return (multiply_matrix4(orientation,
			translation(-from.x, -from.y, -from.z)));
}

t_camera	*camera(float hsize, float vsize, float field_of_view)
{
	float		aspect;
	t_camera	*c;

	c = (t_camera *)ft_calloc(1, sizeof(t_camera));
	c->hsize = hsize;
	c->vsize = vsize;
	c->field_of_view = field_of_view;
	c->transform = identity_matrix4();
	aspect = hsize / vsize;
	if (aspect >= 1)
	{
		c->half_width = tan(c->field_of_view / 2);
		c->half_height = c->half_width / aspect;
	}
	else
	{
		c->half_height = tan(c->field_of_view / 2);
		c->half_width = c->half_height * aspect;
	}
	c->pixel_size = (c->half_width * 2) / c->hsize;
	return (c);
}

t_ray	ray_for_pixel(t_camera *camera, float px, float py)
{
	t_tup2	offset;
	t_tup2	worldc;
	t_tup4	origin;
	t_tup4	pixel;
	t_tup4	direction;

	offset.x = (px + 0.5) * camera->pixel_size;
	offset.y = (py + 0.5) * camera->pixel_size;
	worldc.x = camera->half_width - offset.x;
	worldc.y = camera->half_height - offset.y;
	pixel = matrix4_mult_tup4(invert_matrix4(camera->transform),
			point(worldc.x, worldc.y, -1));
	origin = matrix4_mult_tup4(invert_matrix4(
				camera->transform), point(0, 0, 0));
	direction = normalize(subtract_tup4(pixel, origin));
	return (ray(origin, direction));
}
