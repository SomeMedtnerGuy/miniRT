/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:35:33 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/05 11:40:00 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned char	float_to_shade(float color_strength)
{
	return ((unsigned char)ft_clamp((int)(color_strength * 255.0),
		0, 255));
}

int	tuple_to_color(t_tup4 tup4)
{
	return (float_to_shade(tup4.r) << 16
		| float_to_shade(tup4.g) << 8 | float_to_shade(tup4.b));
}
