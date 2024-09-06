/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:32:47 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/06 16:44:55 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	*hit(t_intersection *xs)
{
	t_intersection	*hit;
	t_intersection	*xs_current;
	t_intersection	*current_intersection;

	hit = NULL;
	xs_current = xs;
	while (xs_current)
	{
		current_intersection = xs_current;

		if (current_intersection->t > 0 && (!hit || current_intersection->t < hit->t))
			hit = xs_current;
		xs_current = xs_current->next;
	}
	return hit;
}

t_intersection	*intersection(float value, void *object)
{
	t_intersection	*new;

	new = ft_calloc(1, sizeof(t_intersection));
	if (new == NULL)
		return (NULL);
	new->t = value;
	new->o = object;
	new->next = NULL;
	return (new);
}
