/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tranformation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:47:19 by joamonte          #+#    #+#             */
/*   Updated: 2024/08/30 18:20:58 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	tran(t_tup4 *point, t_tup4 translator)
{
	if (translator.w == 0)
		return ;
	else if (translator.w == 1)
	{
		point->x += translator.x;
		point->y += translator.y;
		point->z += translator.z;
	}
}

void	inv_translation(t_tup4 *point, t_tup4 translator)
{
	if (translator.w == 0)
		return ;
	else if (translator.w == 1)
	{
	point->x -= translator.x;
	point->y -= translator.y;
	point->z -= translator.z;
	}
}

void	translation(t_tup4 a, float x, float y, float z)
{
	t_matrix4	translator;

	translator = matrix4(tup4(1, 0, 0, x), tup4(0, 1, 0, y),
					tup4(0, 0, 1, z), tup4(0, 0, 0, 1));

	if (a.w == 0)
		return ;
	
}