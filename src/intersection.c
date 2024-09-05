/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:32:47 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/05 17:36:40 by ndo-vale         ###   ########.fr       */
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
	new->object = object;
	new->next = NULL;
	return (new);
}

int	int_size(t_intersection *lst)
{
	int		count;
	t_intersection	*next_value;

	count = 0;
	next_value = lst;
	while (next_value)
	{
		count++;
		next_value = next_value->next;
	}
	return (count);
}

t_intersection	*intlast(t_intersection *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	int_add_back(t_intersection **lst, t_intersection *new)
{
	if (!new)
		return (1);
	if (*lst == NULL)
		*lst = new;
	else
		intlast(*lst)->next = new;
	return (0);
}

