/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_factory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:55:47 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/30 19:51:23 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix2	matrix2(t_tup2 x, t_tup2 y)
{
    t_matrix2   out;

    out.t[0] = x;
    out.t[1] = y;
    return (out);
}

t_matrix3	matrix3(t_tup3 x, t_tup3 y, t_tup3 z)
{
    t_matrix3   out;

    out.t[0] = x;
    out.t[1] = y;
    out.t[2] = z;
    return (out);
}

t_matrix4    matrix4(t_tup4 x, t_tup4 y, t_tup4 z, t_tup4 w)
{
    t_matrix4    out;

    out.t[0] = x;
    out.t[1] = y;
    out.t[2] = z;
    out.t[3] = w;
    return (out);
}

t_matrix4   identity_matrix4(void)
{
    return (matrix4(tup4(1, 0, 0, 0), tup4(0, 1, 0, 0),
                    tup4(0, 0, 1, 0), tup4(0, 0, 0, 1)));
}

t_matrix4   translation(float x, float y, float z)
{
    return (matrix4(tup4(1, 0, 0, x),
                    tup4(0, 1, 0, y),
                    tup4(0, 0, 1, z),
                    tup4(0, 0, 0, 1)));
}

t_matrix4   scaling(float x, float y, float z)
{
    return (matrix4(tup4(x, 0, 0, 0),
                    tup4(0, y, 0, 0),
                    tup4(0, 0, z, 0),
                    tup4(0, 0, 0, 1)));
}

t_matrix4   rotation_x(float r)
{
    return (matrix4(tup4(1, 0, 0, 0),
                    tup4(0, cos(r), -sin(r), 0),
                    tup4(0, sin(r), cos(r), 0),
                    tup4(0, 0, 0, 1)));
}

t_matrix4   rotation_y(float r)
{
    return (matrix4(tup4(cos(r), 0, sin(r), 0),
                    tup4(0, 1, 0, 0),
                    tup4(-sin(r), 0, cos(r), 0),
                    tup4(0, 0, 0, 1)));
}

t_matrix4   rotation_z(float r)
{
    return (matrix4(tup4(cos(r), -sin(r), 0, 0),
                    tup4(sin(r), cos(r), 0, 0),
                    tup4(0, 0, 1, 0),
                    tup4(0, 0, 0, 1)));
}

t_matrix4   shearing(t_tup2 x, t_tup2 y, t_tup2 z)
{
    return (matrix4(tup4(1, x.e[0], x.e[1], 0),
                    tup4(y.e[0], 1, y.e[1], 0),
                    tup4(z.e[0], z.e[1], 1, 0),
                    tup4(0, 0, 0, 1)));
}