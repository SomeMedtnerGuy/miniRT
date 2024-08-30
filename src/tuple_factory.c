/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:43:48 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/30 13:15:05 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tup2  tup2(float x, float y)
{
    t_tup2  out;

    out.e[0] = x;
    out.e[1] = y;
    return (out);
}

t_tup3  tup3(float x, float y, float z)
{
    t_tup3  out;

    out.e[0] = x;
    out.e[1] = y;
    out.e[2] = z;
    return (out);
}

t_tup4  tup4(float x, float y, float z, float w)
{
    t_tup4  out;

    out.x = x;
    out.y = y;
    out.z = z;
    out.w = w;
    return (out);
}

t_tup4  point(float x, float y, float z)
{
    return (tup4(x, y, z, TPOINT));
}

t_tup4  vector(float x, float y, float z)
{
    return (tup4(x, y, z, TVECTOR));
}

t_tup4  color(float x, float y, float z)
{
    return (tup4(x, y, z, TCOLOR));
}
