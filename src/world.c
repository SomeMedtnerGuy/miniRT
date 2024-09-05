/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:31:27 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/05 11:30:20 by joamonte         ###   ########.fr       */
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
	s1->material->color = color(0.8, 1.0, 0.6);
	s1->material->diffuse = 0.7;
	s1->material->specular = 0.2;
	s2->transform = scaling(0.5, 0.5, 0.5);
	ft_lstadd_back(&w->objects, ft_lstnew(s1));
	ft_lstadd_back(&w->objects, ft_lstnew(s2));
	return (w);
}


