/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:31:27 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/06 15:47:04 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world	*world(void)
{
	t_world	*w;

	w = (t_world *)ft_calloc(1, sizeof(t_world));
	return (w);
}

t_world	*default_world(void)
{
	t_world		*w;
	t_sphere	*s1;
	t_sphere	*s2;

	w = world();
	w->light = point_light(point(-10, 10, -10), color(1, 1, 1));
	s1 = sphere();
	s2 = sphere();
	s1->material = material();
	s1->material->color = color(0.8, 1.0, 0.6);
	s1->material->diffuse = 0.7;
	s1->material->specular = 0.2;
	s2->transform = scaling(0.5, 0.5, 0.5);
	ft_lstadd_back(&(w->objects), ft_lstnew(s1));
	ft_lstadd_back(&(w->objects), ft_lstnew(s2));
	return (w);
}

void	lstadd_xs_sorted(t_intersection **lst, t_intersection *new)
{
	t_intersection	*tmplst;
	t_intersection	*tmpnew;

	if (*lst == NULL)
		*lst = new;
	else
	{
		while (new)
		{
			if ((*lst)->t > new->t)
			{
				tmpnew = new->next;
				new->next = *lst; //this and next is int_add_front!
				*lst = new;
				new = tmpnew;
			}
			else
				break ;
		}
		if (!new)
			return ;
		tmplst = *lst;
		while (tmplst && new)
		{
			if (!tmplst->next)
			{
				tmplst->next = new;
				break ;
			}
			else if (tmplst->next->t > new->t)
			{
				tmpnew = new->next;
				new->next = tmplst->next;
				tmplst->next = new;
				new = tmpnew;
			}
			tmplst = tmplst->next;
			
		}
	}	
}

t_intersection	*intersect_world(t_world *w, t_ray r)
{
	t_list	*current_obj_node;
	t_object	*object;
	t_intersection	*world_xs;

	world_xs = NULL;
	current_obj_node = w->objects;
	while (current_obj_node)
	{
		object = current_obj_node->content;
		if (object->type == SPHERE)
			lstadd_xs_sorted(&world_xs, intersect((t_sphere *)object, r));
		current_obj_node = current_obj_node->next;
	}
	return (world_xs);
}

t_comps	prepare_computations(t_intersection *intersection, t_ray ray)
{
	t_comps	comps;

	comps.t = intersection->t;
	comps.object = (void *)intersection->o;
	comps.point = position(ray, comps.t);
	comps.eyev = negate_tup4(ray.direction);
	comps.normalv = normal_at((t_sphere *)comps.object, comps.point);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tup4(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

t_tup4	shade_hit(t_world *w, t_comps comps)
{
	t_light_data	ld;

	ld.material = ((t_sphere *)comps.object)->material; //CHANGE THIS TO ANY OBJECT'S MATERIAL??
	ld.light = w->light;
	ld.point = comps.point;
	ld.eyev = comps.eyev;
	ld.normalv = comps.normalv;
	return (lighting(&ld));
}

t_tup4	color_at(t_world *w, t_ray r)
{
	t_intersection	*xs;
	t_intersection	*hit_int;
	t_comps			comps;

	xs = intersect_world(w, r);
	hit_int = hit(xs);
	if (!hit_int)
		return (color(0, 0, 0));
	comps = prepare_computations(hit_int, r);
	return (shade_hit(w, comps));
}

t_matrix4	view_transform(t_tup4 from, t_tup4 to, t_tup4 up)
{
	t_tup4	forward;
	t_tup4	left;
	t_tup4	true_up;
	t_matrix4	orientation;

	forward = normalize(subtract_tup4(to, from));
	left = cross(forward, normalize(up));
	true_up = cross(left, forward);
	orientation = matrix4(
		tup4(left.x, left.y, left.z, 0),
		tup4(true_up.x, true_up.y, true_up.z, 0),
		tup4(-forward.x, -forward.y, -forward.z, 0),
		tup4(0, 0, 0, 1));
	return (multiply_matrix4(orientation, 
				translation(-from.x, -from.y, -from.z)));
}

t_camera	*camera(float hsize, float vsize, float field_of_view)
{
	float	aspect;
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

void	render(t_canvas *canvas, t_camera *camera, t_world *world)
{
	int		y;
	int		x;
	t_ray	ray;
	t_tup4	color;

	y = -1;
	while (++y < camera->vsize)
	{
		x = -1;
		while (++x < camera->hsize)
		{
			ray = ray_for_pixel(camera, x, y);
			color = color_at(world, ray);
			put_pixel(canvas, x, y, tuple_to_color(color));
		}
	}
}