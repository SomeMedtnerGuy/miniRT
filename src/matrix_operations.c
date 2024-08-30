/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:50:20 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/30 14:21:28 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool    are_matrix4_equal(t_matrix4 a, t_matrix4 b)
{
    int i;

    i = -1;
    while (++i < 4)
    {
        if (!are_tup4_equal(a.t[i], b.t[i]))
            return (false);
    }
    return (true);
}