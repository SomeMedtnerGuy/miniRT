/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:50:20 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/30 15:58:26 by joamonte         ###   ########.fr       */
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

t_matrix4   multiply_matrix(t_matrix4 a, t_matrix4 b)
{
	t_matrix4	result;
	int			row;
	int			col;
	int			i;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			i = 0;
			result.e[row][col] = dot(a.t[row], get_column_from_matrix4(b, col));
			col++;
		}
		row++;
	}
	return (result);
}
