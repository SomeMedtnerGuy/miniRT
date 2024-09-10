/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:14:30 by joamonte          #+#    #+#             */
/*   Updated: 2024/09/10 10:14:54 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	valid_color(int r, int g, int b)
{
	if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255)
		&& (b >= 0 && b <= 255))
		return (true);
	else
		return (false);
}

bool	valid_vector(float x, float y, float z)
{
	if ((x >= -1.0f && x <= 1.0f) && (y >= -1.0f && y <= 1.0f)
		&& (z >= -1.0f && z <= 1.0f))
		return (true);
	else
		return (false);
}

bool	valid_light(float l)
{
	if (l >= 0.0f && l <= 1.0f)
		return (true);
	else
		return (false);
}
