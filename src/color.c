/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:35:33 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/31 15:36:05 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned char	float_to_shade(float color_strength)
{
	return ((unsigned char)clamp((int)(color_strength * 255.0),
			0, 255));
}

int	tuple_to_color(t_tup4 tup4)
{
	return (float_to_shade(tup4.r) << 16 |
			float_to_shade(tup4.g) << 8 |
			float_to_shade(tup4.b));
}