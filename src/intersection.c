/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:32:47 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/05 14:14:39 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	*intersection(float value, void *object)
{
	t_intersection	*inter;

	inter = ft_calloc(1, sizeof(t_intersection));
	inter->t = value;
	inter->object = object;
	return (inter);
}

t_list	*hit(t_list *xs)
{
	t_list	*hit;
	t_list	*xs_current;

	hit = NULL;
	xs_current = xs;
	while (xs_current)
	{
		// Check if it's a valid intersection and compare 't' values
		t_intersection *current_intersection = (t_intersection *)xs_current->content;

		if (current_intersection->t > 0 && (!hit || current_intersection->t < ((t_intersection *)hit->content)->t))
		{
			hit = xs_current;
		}
		xs_current = xs_current->next;
	}

	return hit;
}
