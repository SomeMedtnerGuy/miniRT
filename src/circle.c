/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:50:34 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/05 17:40:39 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_wall
{
	float	z;
	float	size;
	float	half;
}	t_wall;

typedef struct s_warld
{
	float	x;
	float	y;
}	t_warld;


void	circle(t_root r)
{
	t_ray			R;
	t_ray			R_current;
	t_wall			wall;
	t_warld			world;
	float			pixel_size;
	t_sphere		*S;
	t_tup4			position;
	t_intersection	*xs;
	
	S = sphere();

	R.origin = tup4(0, 0, -5, TPOINT);
	R.direction = tup4(0, 0, 1, TVECTOR);

	wall.z = 10.0f;
	wall.size = 7.0f;
	wall.half = wall.size / 2;
	pixel_size = wall.size / CANVAS_HEIGHT;

	for(float y = 0.0f; y < (CANVAS_HEIGHT - 1); y++)
	{
		world.y = wall.half - pixel_size * y;
		for(float x = 0.0f; x < (CANVAS_HEIGHT - 1); x++)
		{
			world.x = -wall.half + pixel_size * x;
			position = tup4(world.x, world.y, wall.z, TPOINT);
			R_current = ray(R.origin, normalize(subtract_tup4(position, R.origin)));
			xs = intersect(S, R_current);
			if (hit(xs))
				put_pixel(r.canvas, x, y, 0xffffff);
			intclear(&xs);
		}
	}
	free (S);
}