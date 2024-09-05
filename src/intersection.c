/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:32:47 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/05 11:09:53 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_intersection *intersection(float value, void *object)
{
	t_intersection	*inter;

	inter = ft_calloc(1, sizeof(t_intersection));
	inter->t = value;
	inter->object = object;

	return (inter);
}

/* t_intersection	*intersections(t_list	*inter)
{
	t_intersection	*join;
	t_list	*next;
	int j;

	j = 0;
	join = ft_calloc(ft_lstsize(inter), sizeof(t_intersection));

	while(next)
	{
		join[j] = inter;
		i++;
	}


	return (join);
} */

t_intersection	hit(t_intersection *intersections, int count)
{
	int	i;
	t_intersection	hit;

	hit.t = 0.0f;
	i = 0;
	while(i < count)
	{
		if(hit.t == 0 && intersections[i].t > 0)
			hit = intersections[i];
		else if(hit.t > intersections[i].t && intersections[i].t > 0)
			hit = intersections[i];
		i++;
	}
	return (hit);
}
