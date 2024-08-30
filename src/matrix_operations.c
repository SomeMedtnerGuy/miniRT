/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:50:20 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/30 15:14:24 by joamonte         ###   ########.fr       */
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

t_matrix4   multiply_matrix(t_matrix4 a, t_matrix4 b)
{
    t_matrix4   result;
    int         row;
    int         col;
    int         i;
    row = 0;
    while (row < 4)
    {
        col = 0;
        while (col < 4)
        {
            i = 0;
            while (i < 4)
            {
                if (i == 0)
                    result.e[row][col] = a.e[row][i] * b.e[i][col];
                else
                    result.e[row][col] += a.e[row][i] * b.e[i][col];
                i++;
            }
            col++;
        }
        row++;
    }
    return (result);
}