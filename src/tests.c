/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:41:52 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/31 17:26:09 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool    test_tuple(void)
{
    char    *msg = "test_tuple failed!\n";
    t_tup4  a;

    a = tup4(4.3, -4.2, 3.1, 1.0);
    if (!(ft_fcmp(a.x, 4.3)
            && ft_fcmp(a.y, -4.2)
            && ft_fcmp(a.z, 3.1)
            && ft_fcmp(a.w, 1.0)
            && a.w == TPOINT 
            && a.w != TVECTOR))
        return (ft_printf(msg), false);
    a = tup4(4.3, -4.2, 3.1, 0.0);
    if (!(ft_fcmp(a.x, 4.3)
            && ft_fcmp(a.y, -4.2) 
            && ft_fcmp(a.z, 3.1)
            && ft_fcmp(a.w, 0.0)
            && a.w != TPOINT
            && a.w == TVECTOR))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_point(void)
{
    t_tup4  p;

    p = point(4, -4, 3);
    if (!(are_tup4_equal(p, tup4(4, -4, 3, 1))))
        return (ft_printf("test_point failed!\n"), false);
    return (true);
}

bool    test_vector(void)
{
    t_tup4  v;

    v = vector(4, -4, 3);
    if (!(are_tup4_equal(v, tup4(4, -4, 3, 0))))
        return (ft_printf("test_vector failed!\n"), false);
    return (true);
}

bool    test_add_tup4(void)
{
    t_tup4  res;

    res = add_tup4(tup4(3, -2, 5, 1), tup4(-2, 3, 1, 0));
    if (!(are_tup4_equal(res, tup4(1, 1, 6, 1))))
        return (ft_printf("test_add_tup4 failed!\n"), false);
    return (true);
}

bool    test_subtract_tup4(void)
{
    char    *msg = "test_subtract_tup4 failed!\n";
    t_tup4  res;

    res = subtract_tup4(point(3, 2, 1), point(5, 6, 7));
    if (!(are_tup4_equal(res, vector(-2, -4, -6))))
        return (ft_printf(msg), false);
    res = subtract_tup4(point(3, 2, 1), vector(5, 6, 7));
    if (!(are_tup4_equal(res, point(-2, -4, -6))))
        return (ft_printf(msg), false);
    res = subtract_tup4(vector(3, 2, 1), vector(5, 6, 7));
    if (!(are_tup4_equal(res, vector(-2, -4, -6))))
        return (ft_printf(msg), false);
    res = subtract_tup4(vector(0, 0, 0), vector(1, -2, 3));
    if (!(are_tup4_equal(res, vector(-1, 2, -3))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_negate_tup4(void)
{
    t_tup4  res;

    res = negate_tup4(tup4(1, -2, 3, -4));
    if (!(are_tup4_equal(res, tup4(-1, 2, -3, 4))))
        return (ft_printf("test_add_tup4 failed!\n"), false);
    return (true);
}

bool    test_multiply_tup4(void)
{
    char    *msg = "test_add_tup4 failed!\n";
    t_tup4  res;

    res = multiply_tup4(tup4(1, -2, 3, -4), 3.5);
    if (!(are_tup4_equal(res, tup4(3.5, -7, 10.5, -14))))
        return (ft_printf(msg), false);
    res = multiply_tup4(tup4(1, -2, 3, -4), 0.5);
    if (!(are_tup4_equal(res, tup4(0.5, -1, 1.5, -2))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_divide_tup4(void)
{
    char    *msg = "test_divide_tup4 failed!\n";
    t_tup4  res;

    res = divide_tup4(tup4(1, -2, 3, -4), 2);
    if (!(are_tup4_equal(res, tup4(0.5, -1, 1.5, -2))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_magnitude(void)
{
    char    *msg = "test_magnitude failed!\n";
    float  res;

    res = magnitude(vector(1, 0, 0));
    if (!(ft_fcmp(res, 1.0)))
        return (ft_printf(msg), false);
    res = magnitude(vector(0, 1, 0));
    if (!(ft_fcmp(res, 1.0)))
        return (ft_printf(msg), false);
    res = magnitude(vector(0, 0, 1));
    if (!(ft_fcmp(res, 1.0)))
        return (ft_printf(msg), false);
    res = magnitude(vector(1, 2, 3));
    if (!(ft_fcmp(res, sqrt(14))))
        return (ft_printf(msg), false);
    res = magnitude(vector(-1, -2, -3));
    if (!(ft_fcmp(res, sqrt(14))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_normalization(void)
{
    char    *msg = "test_normalization failed!\n";
    t_tup4  res;

    res = normalize(vector(4, 0, 0));
    if (!(are_tup4_equal(res, vector(1, 0, 0))))
        return (ft_printf(msg), false);
    res = normalize(vector(1, 2, 3));
    if (!(are_tup4_equal(res, vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14)))))
        return (ft_printf(msg), false);
    res = normalize(vector(1, 2, 3));
    if (!(ft_fcmp(magnitude(res), 1)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_dot(void)
{
    char    *msg = "test_dot failed!\n";
    float   res;

    res = dot(vector(1, 2, 3), vector(2, 3, 4));
    if (!(ft_fcmp(res, 20)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_cross(void)
{
    char    *msg = "test_cross failed!\n";
    t_tup4  res;

    res = cross(vector(1, 2, 3), vector(2, 3, 4));
    if (!(are_tup4_equal(res, vector(-1, 2, -1))))
        return (ft_printf(msg), false);
    res = cross(vector(2, 3, 4), vector(1, 2, 3));
    if (!(are_tup4_equal(res, vector(1, -2, 1))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_color(void)
{
    char    *msg = "test_color failed!\n";
    t_tup4  res;

    res = color(-0.5, 0.4, 1.7);
    if (!(1))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_(void)
{
    char    *msg = "failed!\n";
    t_tup4  res;

    (void)res;
    if (!(1))
        return (ft_printf(msg), false);
    return (true);
}

void    run_tests(void)
{
    if (test_tuple() && test_point() && test_vector() 
        && test_add_tup4() && test_subtract_tup4()
        && test_negate_tup4() && test_multiply_tup4()
        && test_divide_tup4() && test_magnitude()
        && test_normalization() && test_dot()
        && test_cross())
        printf("All tests passed!!");
}
