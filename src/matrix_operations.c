/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:50:20 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/30 17:35:24 by ndo-vale         ###   ########.fr       */
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

t_matrix4   multiply_matrix4(t_matrix4 a, t_matrix4 b)
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

float   determinant2(t_matrix2 a)
{
    return (a.e[0][0] * a.e[1][1] - a.e[0][1] * a.e[1][0]);
}

t_matrix2   submatrix3(t_matrix3 a, int i, int j)
{
    t_matrix2   out;
    int x1;
    int y1;
    int x2;
    int y2;

    y1 = -1;
    y2 = 0;
    while (++y1 < 3)
    {
        if (y1 == i)
            continue ;
        x1 = -1;
        x2 = -1;
        while (++x1 < 3)
        {
            if (x1 == j)
                continue ;
            out.e[y2][++x2] = a.e[y1][x1];
        }
        y2++;
    }
    return (out);
}

t_matrix3   submatrix4(t_matrix4 a, int i, int j)
{
    t_matrix3   out;
    int x1;
    int y1;
    int x2;
    int y2;

    y1 = -1;
    y2 = 0;
    while (++y1 < 4)
    {
        if (y1 == i)
            continue ;
        x1 = -1;
        x2 = -1;
        while (++x1 < 4)
        {
            if (x1 == j)
                continue ;
            out.e[y2][++x2] = a.e[y1][x1];
        }
        y2++;
    }
    return (out);
}

float   cofactor3(t_matrix3 a, int i, int j)
{
    if ((i + j) % 2 == 0)
        return(determinant2(submatrix3(a, i, j)));
    return(-determinant2(submatrix3(a, i, j)));
}

float   determinant3(t_matrix3 a)
{
    int     i;
    float   out;

    i = -1;
    out = 0.0;
    while (++i < 3)
        out += a.e[0][i] * cofactor3(a, 0, i);
    return (out);
}

float   cofactor4(t_matrix4 a, int i, int j)
{
    if ((i + j) % 2 == 0)
        return(determinant3(submatrix4(a, i, j)));
    return(-determinant3(submatrix4(a, i, j)));
}

float   determinant4(t_matrix4 a)
{
    int     i;
    float   out;

    i = -1;
    out = 0.0;
    while (++i < 4)
        out += a.e[0][i] * cofactor4(a, 0, i);
    return (out);
}

bool    is_matrix4_invertible(t_matrix4 a)
{
    return (determinant4(a));
}

t_matrix4   build_cofactor_matrix(t_matrix4 a)
{
    int i;
    int j;
    t_matrix4   out;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            out.e[i][j] = cofactor4(a, i, j);
    }
    return (out);
}

t_matrix4   invert_matrix4(t_matrix4 a)
{
    t_matrix4   transposed_cofactors;
    float       determinant;
    int i;
    int j;

    transposed_cofactors = transpose_matrix4(build_cofactor_matrix(a));
    determinant = determinant4(a);
    i = -1;
    while (++i < 4)
    {
            j = -1;
            while (++j < 4)
                a.e[i][j] = transposed_cofactors.e[i][j] / determinant;
    }
    return (a);
}