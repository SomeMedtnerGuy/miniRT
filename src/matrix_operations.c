/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:50:20 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/30 14:57:05 by ndo-vale         ###   ########.fr       */
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

t_tup4	get_column_from_matrix4(t_matrix4 a, int i)
{
    return(tup4(a.e[0][i], a.e[1][i], a.e[2][i], a.e[3][i]));
}

t_matrix4   transpose_matrix4(t_matrix4 a)
{
    return (matrix4(get_column_from_matrix4(a, 0),
                    get_column_from_matrix4(a, 1),
                    get_column_from_matrix4(a, 2),
                    get_column_from_matrix4(a, 3)));
}