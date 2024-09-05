/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:31:27 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/05 19:29:54 by ndo-vale         ###   ########.fr       */
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
	comps.object = (void *)intersection->object;
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
	t_intersection	*hit;
	t_comps			comps;

	xs = intersect_world(w, r);
	hit = hit(xs);
	if (!hit)
		return (color(0, 0, 0));
	comps = prepare_computations(hit, r);
	return (shade_hit(w, comps));
}