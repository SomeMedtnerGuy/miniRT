/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:41:52 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/06 12:22:35 by ndo-vale         ###   ########.fr       */
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
    if (!(tup4cmp(p, tup4(4, -4, 3, 1))))
        return (ft_printf("test_point failed!\n"), false);
    return (true);
}

bool    test_vector(void)
{
    t_tup4  v;

    v = vector(4, -4, 3);
    if (!(tup4cmp(v, tup4(4, -4, 3, 0))))
        return (ft_printf("test_vector failed!\n"), false);
    return (true);
}

bool    test_add_tup4(void)
{
    t_tup4  res;

    res = add_tup4(tup4(3, -2, 5, 1), tup4(-2, 3, 1, 0));
    if (!(tup4cmp(res, tup4(1, 1, 6, 1))))
        return (ft_printf("test_add_tup4 failed!\n"), false);
    return (true);
}

bool    test_subtract_tup4(void)
{
    char    *msg = "test_subtract_tup4 failed!\n";
    t_tup4  res;

    res = subtract_tup4(point(3, 2, 1), point(5, 6, 7));
    if (!(tup4cmp(res, vector(-2, -4, -6))))
        return (ft_printf(msg), false);
    res = subtract_tup4(point(3, 2, 1), vector(5, 6, 7));
    if (!(tup4cmp(res, point(-2, -4, -6))))
        return (ft_printf(msg), false);
    res = subtract_tup4(vector(3, 2, 1), vector(5, 6, 7));
    if (!(tup4cmp(res, vector(-2, -4, -6))))
        return (ft_printf(msg), false);
    res = subtract_tup4(vector(0, 0, 0), vector(1, -2, 3));
    if (!(tup4cmp(res, vector(-1, 2, -3))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_negate_tup4(void)
{
    t_tup4  res;

    res = negate_tup4(tup4(1, -2, 3, -4));
    if (!(tup4cmp(res, tup4(-1, 2, -3, 4))))
        return (ft_printf("test_add_tup4 failed!\n"), false);
    return (true);
}

bool    test_multiply_tup4(void)
{
    char    *msg = "test_add_tup4 failed!\n";
    t_tup4  res;

    res = multiply_tup4(tup4(1, -2, 3, -4), 3.5);
    if (!(tup4cmp(res, tup4(3.5, -7, 10.5, -14))))
        return (ft_printf(msg), false);
    res = multiply_tup4(tup4(1, -2, 3, -4), 0.5);
    if (!(tup4cmp(res, tup4(0.5, -1, 1.5, -2))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_divide_tup4(void)
{
    char    *msg = "test_divide_tup4 failed!\n";
    t_tup4  res;

    res = divide_tup4(tup4(1, -2, 3, -4), 2);
    if (!(tup4cmp(res, tup4(0.5, -1, 1.5, -2))))
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
    if (!(tup4cmp(res, vector(1, 0, 0))))
        return (ft_printf(msg), false);
    res = normalize(vector(1, 2, 3));
    if (!(tup4cmp(res, vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14)))))
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
    if (!(tup4cmp(res, vector(-1, 2, -1))))
        return (ft_printf(msg), false);
    res = cross(vector(2, 3, 4), vector(1, 2, 3));
    if (!(tup4cmp(res, vector(1, -2, 1))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_color(void)
{
    char    *msg = "test_color failed!\n";
    t_tup4  res;

    res = color(-0.5, 0.4, 1.7);
    if (!(ft_fcmp(res.r, -0.5) && ft_fcmp(res.g, 0.4) && ft_fcmp(res.b, 1.7)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_hadamard(void)
{
    char    *msg = "test_hadamard failed!\n";
    t_tup4  res;

    res = hadamard(color(1, 0.2, 0.4), color(0.9, 1, 0.1));
    if (!(tup4cmp(res, color(0.9, 0.2, 0.04))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_matrix2(void)
{
    char    *msg = "test_matrix2 failed!\n";
    t_matrix2  res;

    res = matrix2(tup2(-3, 5), tup2(1, -2));
    if (!(ft_fcmp(res.e[0][0], -3)
            && ft_fcmp(res.e[0][1], 5)
            && ft_fcmp(res.e[1][0], 1)
            && ft_fcmp(res.e[1][1], -2)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_matrix3(void)
{
    char    *msg = "test_matrix3 failed!\n";
    t_matrix3  res;

    res = matrix3(tup3(-3, 5, 0),
                    tup3(1, -2, -7),
                    tup3(0, 1, 1));
    if (!(ft_fcmp(res.e[0][0], -3)
            && ft_fcmp(res.e[1][1], -2)
            && ft_fcmp(res.e[2][2], 1)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_matrix4(void)
{
    char    *msg = "test_matrix4 failed!\n";
    t_matrix4  res;

    res = matrix4(tup4(1, 2, 3, 4),
                    tup4(5.5, 6.5, 7.5, 8.5),
                    tup4(9, 10, 11, 12),
                    tup4(13.5, 14.5, 15.5, 16.5));
    if (!(ft_fcmp(res.e[0][0], 1)
            && ft_fcmp(res.e[0][3], 4)
            && ft_fcmp(res.e[1][0], 5.5)
            && ft_fcmp(res.e[1][2], 7.5)
            && ft_fcmp(res.e[2][2], 11)
            && ft_fcmp(res.e[3][0], 13.5)
            && ft_fcmp(res.e[3][2], 15.5)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_matrix4cmp(void)
{
    char    *msg = "test_matrix4cmp failed!\n";
    t_matrix4   a;
    t_matrix4   b;

    a = matrix4(tup4(1, 2, 3, 4),
                    tup4(5, 6, 7, 8),
                    tup4(9, 8, 7, 6),
                    tup4(5, 4, 3, 2));
    b = matrix4(tup4(1, 2, 3, 4),
                    tup4(5, 6, 7, 8),
                    tup4(9, 8, 7, 6),
                    tup4(5, 4, 3, 2));
    if (!(matrix4cmp(a, b)))
        return (ft_printf(msg), false);
    b = matrix4(tup4(2, 3, 4, 5),
                    tup4(6, 7, 8, 9),
                    tup4(8, 7, 6, 5),
                    tup4(4, 3, 2, 1));
    if (!(matrix4cmp(a, b) == false))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_multiply_matrix4(void)
{
    char        *msg = "test_multiply_matrix4 failed!\n";
    t_matrix4   a;
    t_matrix4   b;
    t_matrix4   res;

    a = matrix4(tup4(1, 2, 3, 4),
                    tup4(5, 6, 7, 8),
                    tup4(9, 8, 7, 6),
                    tup4(5, 4, 3, 2));
    b = matrix4(tup4(-2, 1, 2, 3),
                    tup4(3, 2, 1, -1),
                    tup4(4, 3, 6, 5),
                    tup4(1, 2, 7, 8));
    res = matrix4(tup4(20, 22, 50, 48),
                    tup4(44, 54, 114, 108),
                    tup4(40, 58, 110, 102),
                    tup4(16, 26, 46, 42));
    if (!(matrix4cmp(multiply_matrix4(a, b), res)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_matrix4_mult_tup4(void)
{
    char    *msg = "test_matrix4_mult_tup4 failed!\n";
    t_matrix4   m;
    t_tup4      t;
    t_tup4      res;

    m = matrix4(tup4(1, 2, 3, 4),
                    tup4(2, 4, 4, 2),
                    tup4(8, 6, 4, 1),
                    tup4(0, 0, 0, 1));
    t = tup4(1, 2, 3, 1);
    res = tup4(18, 24, 33, 1);
    if (!(tup4cmp(matrix4_mult_tup4(m, t), res)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_identity_matrix(void)
{
    char    *msg = "test_identity_matrix failed!\n";
    t_matrix4   m;
    t_tup4      t;

    m = matrix4(tup4(0, 1, 2, 4),
                    tup4(1, 2, 4, 8),
                    tup4(2, 4, 8, 16),
                    tup4(4, 8, 16, 32));
    t = tup4(1, 2, 3, 4);
    if (!(matrix4cmp(multiply_matrix4(m, identity_matrix4()), m)))
        return (ft_printf(msg), false);
    if (!(tup4cmp(matrix4_mult_tup4(identity_matrix4(), t), t)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_transpose_matrix4(void)
{
    char    *msg = "test_transpose failed!\n";
    t_matrix4   m;
    t_matrix4   res;

    m = matrix4(tup4(0, 9, 3, 0),
                    tup4(9, 8, 0, 8),
                    tup4(1, 8, 5, 3),
                    tup4(0, 0, 5, 8));
    res = matrix4(tup4(0, 9, 1, 0),
                    tup4(9, 8, 8, 0),
                    tup4(3, 0, 5, 5),
                    tup4(0, 8, 3, 8));
    if (!(matrix4cmp(transpose_matrix4(m), res)))
        return (ft_printf(msg), false);
    if (!(matrix4cmp(transpose_matrix4(identity_matrix4()),
                    identity_matrix4())))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_determinant2(void)
{
    char    *msg = "determinant2 failed!\n";

    if (!(determinant2(matrix2(tup2(1, 5), tup2(-3, 2))) == 17))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_submatrix3(void)
{
    char    *msg = "test_submatrix3 failed!\n";
    t_matrix2  res;

    res = submatrix3(matrix3(tup3(1, 5, 0),
                                tup3(-3, 2, 7),
                                tup3(0, 6, -3)), 0, 2);
    if (!(matrix2cmp(res, matrix2(tup2(-3, 2), tup2(0, 6)))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_submatrix4(void)
{
    char    *msg = "test_submatrix4 failed!\n";
    t_matrix3   res;

    res = submatrix4(matrix4(tup4(-6, 1, 1, 6),
                                tup4(-8, 5, 8, 6),
                                tup4(-1, 0, 8, 2),
                                tup4(-7, 1, -1, 1)), 2, 1);
    if (!(matrix3cmp(res, matrix3(tup3(-6, 1, 6),
                                    tup3(-8, 8, 6),
                                    tup3(-7, -1, 1)))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_cofactor3(void)
{
    char    *msg = "cofactor3 failed!\n";
    t_matrix3  res;

    res = matrix3(tup3(3, 5, 0),
                    tup3(2, -1, -7),
                    tup3(6, -1, 5));
    if (!(cofactor3(res, 0, 0) == -12 && cofactor3(res, 1, 0) == -25))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_cofactor4(void)
{
    char    *msg = "cofactor4 failed!\n";
    t_matrix4  res;

    res = matrix4(tup4(-2, -8, 3, 5),
                    tup4(-3, 1, 7, 3),
                    tup4(1, 2, -9, 6),
                    tup4(-6, 7, 7, -9));
    if (!(cofactor4(res, 0, 0) == 690
            && cofactor4(res, 0, 1) == 447
            && cofactor4(res, 0, 2) == 210
            && cofactor4(res, 0, 3) == 51))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_detetrminant3(void)
{
    char    *msg = "determinant3 failed!\n";
    t_matrix3  m;

    m = matrix3(tup3(1, 2, 6),
                tup3(-5, 8, -4),
                tup3(2, 6, 4));
    if (!(determinant3(m) == -196))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_detetrminant4(void)
{
    char    *msg = "determinant4 failed!\n";
    t_matrix4  m;

    m = matrix4(tup4(-2, -8, 3, 5),
                tup4(-3, 1, 7, 3),
                tup4(1, 2, -9, 6),
                tup4(-6, 7, 7, -9));
    if (!(determinant4(m) == -4071))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_is_matrix4_invertible(void)
{
    char    *msg = "test_is_matrix4_invertible failed!\n";
    t_matrix4  m;

    m = matrix4(tup4(6, 4, 4, 4),
                tup4(5, 5, 7, 6),
                tup4(4, -9, 3, -7),
                tup4(9, 1, 7, -6));
    if (!(is_matrix4_invertible(m)))
        return (ft_printf(msg), false);
    m = matrix4(tup4(-4, 2, -2, -3),
                tup4(9, 6, 2, 6),
                tup4(0, -5, 1, -5),
                tup4(0, 0, 0, 0));
    if (!(!is_matrix4_invertible(m)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_invert_matrix4(void)
{
    char    *msg = "test_invert_matrix4 failed!\n";
    t_matrix4   res;
    t_matrix4   cmp;

    res = matrix4(tup4(-5, 2, 6, -8),
                tup4(1, -5, 1, 8),
                tup4(7, 7, -6, -7),
                tup4(1, -3, 7, 4));
    cmp = matrix4(tup4(0.21805, 0.45113, 0.24060, -0.04511),
                tup4(-0.80827, -1.45677, -0.44361, 0.52068),
                tup4(-0.07895, -0.22368, -0.05263, 0.19737),
                tup4(-0.52256, -0.81391, -0.30075, 0.30639));
    if (!(matrix4cmp(invert_matrix4(res), cmp)))
        return (ft_printf(msg), false);
    res = matrix4(tup4(8, -5, 9, 2),
                tup4(7, 5, 6, 1),
                tup4(-6, 0, 9, 6),
                tup4(-3, 0, -9, -4));
    cmp = matrix4(tup4(-0.15385, -0.15385, -0.28205, -0.53846),
                tup4(-0.07692, 0.12308, 0.02564, 0.03077),
                tup4(0.35897, 0.35897, 0.43590, 0.92308),
                tup4(-0.69231, -0.69231, -0.76923, -1.92308));
    if (!(matrix4cmp(invert_matrix4(res), cmp)))
        return (ft_printf(msg), false);
    res = matrix4(tup4(9, 3, 0, 9),
                tup4(-5, -2, -6, -3),
                tup4(-4, 9, 6, 4),
                tup4(-7, 6, 6, 2));
    cmp = matrix4(tup4(-0.04074, -0.07778, 0.14444, -0.22222),
                tup4(-0.07778, 0.03333, 0.36667, -0.33333),
                tup4(-0.02901, -0.14630, -0.10926, 0.12963),
                tup4(0.17778, 0.06667, -0.26667, 0.33333));
    if (!(matrix4cmp(invert_matrix4(res), cmp)))
        return (ft_printf(msg), false);
    t_matrix4   a = matrix4(tup4(3, -9, 7, 3),
                tup4(3, -8, 2, -9),
                tup4(-4, 4, 4, 1),
                tup4(-6, 5, -1, 1));
    t_matrix4   b = matrix4(tup4(8, 2, 2, 2),
                tup4(3, -1, 7, 0),
                tup4(7, 0, 5, 4),
                tup4(6, -2, 0, 5));
    t_matrix4   c = multiply_matrix4(a, b);
    res = multiply_matrix4(c, invert_matrix4(b));
    if (!(matrix4cmp(a, res)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_translation(void)
{
    char    *msg = "test_translation failed!\n";
    
    t_matrix4   transform = translation(5, -3, 2);
    t_tup4      p = point(-3, 4, 5);
    if (!(tup4cmp(matrix4_mult_tup4(transform, p), point(2, 1, 7))))
        return (ft_printf(msg), false);
    if (!(tup4cmp(matrix4_mult_tup4(invert_matrix4(transform), p),
                    point(-8, 7, 3))))
        return (ft_printf(msg), false);
    t_tup4      v = vector(-3, 4, 5);
    if (!(tup4cmp(matrix4_mult_tup4(transform, v),v)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_scaling(void)
{
    char    *msg = "test_scaling failed!\n";
    t_matrix4  t;
    t_tup4      p;
    t_tup4      v;

    t = scaling(2, 3, 4);
    p = point(-4, 6, 8);
    if (!(tup4cmp(matrix4_mult_tup4(t, p), point(-8, 18, 32))))
        return (ft_printf(msg), false);
    v = vector(-4, 6, 8);
    if (!(tup4cmp(matrix4_mult_tup4(t, v), vector(-8, 18, 32))))
        return (ft_printf(msg), false);
    if (!(tup4cmp(matrix4_mult_tup4(invert_matrix4(t), v), vector(-2, 2, 2))))
        return (ft_printf(msg), false);
    t = scaling(-1, 1, 1);
    p = point(2, 3, 4);
    if (!(tup4cmp(matrix4_mult_tup4(t, p), point(-2, 3, 4))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_rotation_x(void)
{
    char    *msg = "test_rotation_x failed!\n";
    t_matrix4   t;
    t_tup4      p;
    t_tup4      res;

    p = point(0, 1, 0);
    t = rotation_x(M_PI / 4);
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(0, sqrt(2) / 2, sqrt(2) / 2))))
        return (ft_printf("1\n"), ft_printf(msg), false);
    res = matrix4_mult_tup4(invert_matrix4(t), p);
    if (!(tup4cmp(res, point(0, (sqrt(2) / 2), -(sqrt(2) / 2)))))
        return (ft_printf("2\n"), ft_printf(msg), false);
    t = rotation_x(M_PI / 2);
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(0, 0, 1))))
        return (ft_printf("3\n"), ft_printf(msg), false);
    return (true);
}

bool    test_rotation_y(void)
{
    char    *msg = "test_rotation_y failed!\n";
    t_matrix4   t;
    t_tup4      p;
    t_tup4      res;

    p = point(0, 0, 1);
    t = rotation_y(M_PI / 4);
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(sqrt(2) / 2, 0, sqrt(2) / 2))))
        return (ft_printf(msg), false);
    res = matrix4_mult_tup4(invert_matrix4(t), p);
    if (!(tup4cmp(res, point(-(sqrt(2) / 2), 0, (sqrt(2) / 2)))))
        return (ft_printf(msg), false);
    t = rotation_y(M_PI / 2);
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(1, 0, 0))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_rotation_z(void)
{
    char    *msg = "test_rotation_z failed!\n";
    t_matrix4   t;
    t_tup4      p;
    t_tup4      res;

    p = point(0, 1, 0);
    t = rotation_z(M_PI / 4);
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(-(sqrt(2) / 2), (sqrt(2) / 2), 0))))
        return (ft_printf(msg), false);
    res = matrix4_mult_tup4(invert_matrix4(t), p);
    if (!(tup4cmp(res, point((sqrt(2) / 2), (sqrt(2) / 2), 0))))
        return (ft_printf(msg), false);
    t = rotation_z(M_PI / 2);
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(-1, 0, 0))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_shearing(void)
{
    char    *msg = "test_shearing failed!\n";
    t_matrix4   t;
    t_tup4      p;
    t_tup4      res;

    p = point(2, 3, 4);
    t = shearing(tup2(1, 0), tup2(0, 0), tup2(0, 0));
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(5, 3, 4))))
        return (ft_printf(msg), false);
    t = shearing(tup2(0, 1), tup2(0, 0), tup2(0, 0));
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(6, 3, 4))))
        return (ft_printf(msg), false);
    t = shearing(tup2(0, 0), tup2(1, 0), tup2(0, 0));
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(2, 5, 4))))
        return (ft_printf(msg), false);
    t = shearing(tup2(0, 0), tup2(0, 1), tup2(0, 0));
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(2, 7, 4))))
        return (ft_printf(msg), false);
    t = shearing(tup2(0, 0), tup2(0, 0), tup2(1, 0));
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(2, 3, 6))))
        return (ft_printf(msg), false);
    t = shearing(tup2(0, 0), tup2(0, 0), tup2(0, 1));
    res = matrix4_mult_tup4(t, p);
    if (!(tup4cmp(res, point(2, 3, 7))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_sphere_normal(void)
{
    char    *msg = "test_sphere_normal falied!!\n";
    t_sphere    *s;
    t_tup4      n;

    s = sphere();
    n = normal_at(s, point(1, 0, 0));
    if (!(tup4cmp(n, vector(1, 0, 0))))
        return (ft_printf(msg), false);
    n = normal_at(s, point(0, 1, 0));
    if (!(tup4cmp(n, vector(0, 1, 0))))
        return (ft_printf(msg), false);
    n = normal_at(s, point(0, 0, 1));
    if (!(tup4cmp(n, vector(0, 0, 1))))
        return (ft_printf(msg), false);
    n = normal_at(s, point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    if (!(tup4cmp(n, vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3))))
        return (ft_printf(msg), false);
    n = normal_at(s, point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    if (!(tup4cmp(n, normalize(n))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_reflect(void)
{
    char    *msg = "test_reflect failed!\n";
    t_tup4  v;
    t_tup4  n;
    t_tup4  r;

    v = vector(1, -1, 0);
    n = vector(0, 1, 0);
    r = reflect(v, n);
    if (!(tup4cmp(r, vector(1, 1, 0))))
        return (ft_printf(msg), false);
    v = vector(0, -1, 0);
    n = vector(sqrt(2) / 2, sqrt(2) / 2, 0);
    r = reflect(v, n);
    if (!(tup4cmp(r, vector(1, 0, 0))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_lighting(void)
{
    char    *msg = "test_lighting failed!\n";
    t_material  *m;
    t_light_data    ld;

    m = material();
    ld.material = m;
    ld.point = point(0, 0, 0);

    ld.eyev = vector(0, 0, -1);
    ld.normalv = vector(0, 0, -1);
    ld.light = point_light(point(0, 0, -10), color(1, 1, 1)); 
    if (!(tup4cmp(lighting(&ld), color(1.9, 1.9, 1.9))))
        return (ft_printf(msg), false);
    ld.eyev = vector(0, sqrt(2) / 2, -sqrt(2) / 2);
    ld.normalv = vector(0, 0, -1);
    ld.light = point_light(point(0, 0, -10), color(1, 1, 1)); 
    if (!(tup4cmp(lighting(&ld), color(1.0, 1.0, 1.0))))
        return (ft_printf(msg), false);
    ld.eyev = vector(0, 0, -1);
    ld.normalv = vector(0, 0, -1);
    ld.light = point_light(point(0, 10, -10), color(1, 1, 1)); 
    if (!(tup4cmp(lighting(&ld), color(0.7364, 0.7364, 0.7364))))
        return (ft_printf(msg), false);
    ld.eyev = vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
    ld.normalv = vector(0, 0, -1);
    ld.light = point_light(point(0, 10, -10), color(1, 1, 1)); 
    if (!(tup4cmp(lighting(&ld), color(1.63638, 1.63638, 1.63638))))
        return (ft_printf(msg), false);
    ld.eyev = vector(0, 0, -1);
    ld.normalv = vector(0, 0, -1);
    ld.light = point_light(point(0, 0, 10), color(1, 1, 1)); 
    if (!(tup4cmp(lighting(&ld), color(0.1, 0.1, 0.1))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_world(void)
{
    char    *msg = "test_world failed!\n";
    t_world         *w;
    t_ray           r;
    t_intersection  *xs;

    w = world();
    if (!(w->light == NULL && w->objects == NULL))
        return (ft_printf(msg), false);
    w = default_world();
    if (!(w->light && w->objects && w->objects->next
            && !w->objects->next->next))
        return (ft_printf(msg), false);
    r = ray(point(0, 0, -5), vector(0, 0, 1));
    xs = intersect_world(w, r);
    if (!(/*ft_lstsize(xs) == 4 && */xs->t == 4
            && xs->next->t == 4.5
            && xs->next->next->t == 5.5
            && xs->next->next->next->t == 6))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_prepare_computations(void)
{
    char    *msg = "test_prepare_computations failed!\n";
    t_ray           r;
    t_object        *shape;
    t_intersection  *i;
    t_comps         comps;

    r = ray(point(0, 0, -5), vector(0, 0, 1));
    shape = (t_object *)sphere(); //perhaps every object should return this type
    i = intersection(4, shape);
    comps = prepare_computations(i, r);
    if (!(comps.t == i->t && comps.object == i->o
        && tup4cmp(comps.point, point(0, 0, -1))
        && tup4cmp(comps.eyev, vector(0, 0, -1))
        && tup4cmp(comps.normalv, vector(0, 0, -1))
        && comps.inside == false))
        return (ft_printf(msg), false);
    r = ray(point(0, 0, 0), vector(0, 0, 1));
    i = intersection(1, shape);
    comps = prepare_computations(i, r);
    if (!(comps.t == i->t && comps.object == i->o
        && tup4cmp(comps.point, point(0, 0, 1))
        && tup4cmp(comps.eyev, vector(0, 0, -1))
        && tup4cmp(comps.normalv, vector(0, 0, -1))
        && comps.inside == true))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_shade_hit(void)
{
    char    *msg = "test_shade_hit failed!\n";
    
    t_world *w = default_world();
    t_ray   r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_object    *shape = (t_object *)w->objects->content;
    t_intersection  *i = intersection(4, shape);
    t_comps comps = prepare_computations(i, r);
    t_tup4  c = shade_hit(w, comps);
    if (!(tup4cmp(c, color(0.38066, 0.47583, 0.2855))))
        return (ft_printf(msg), false);
    w = default_world();
    w->light = point_light(point(0, 0.25, 0), color(1, 1, 1));
    r = ray(point(0, 0, 0), vector(0, 0, 1));
    shape = (t_object *)w->objects->next->content;
    i = intersection(0.5, shape);
    comps = prepare_computations(i, r);
    c = shade_hit(w, comps);
    if (!(tup4cmp(c, color(0.90498, 0.90498, 0.90498))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_color_at(void)
{
    char    *msg = "test_color_at failed!\n";
    
    t_world *w = default_world();
    t_ray   r = ray(point(0, 0, 5), vector(0, 1, 0));
    t_tup4  c = color_at(w, r);
    if (!(tup4cmp(c, color(0, 0, 0))))
        return (ft_printf(msg), false);
    r = ray(point(0, 0, -5), vector(0, 0, 1));
    c = color_at(w, r);
    if (!(tup4cmp(c, color(0.38066, 0.47583, 0.2855))))
        return (ft_printf(msg), false);
    ((t_sphere *)w->objects->content)->material->ambient = 1;
    ((t_sphere *)w->objects->next->content)->material->ambient = 1;
    r = ray(point(0, 0, 0.75), vector(0, 0, -1));
    c = color_at(w, r);
    if (!(tup4cmp(c, ((t_sphere *)w->objects->next->content)->material->color)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_view_transform(void)
{
    char    *msg = "test_view_transform failed!\n";
    t_tup4  from;
    t_tup4  to;
    t_tup4  up;
    t_matrix4   t;

    from = point(0, 0, 0);
    to = point(0, 0, -1);
    up = vector(0, 1, 0);
    t = view_transform(from, to, up);
    if (!(matrix4cmp(t, identity_matrix4())))
        return (ft_printf(msg), false);
    from = point(0, 0, 0);
    to = point(0, 0, 1);
    up = vector(0, 1, 0);
    t = view_transform(from, to, up);
    if (!(matrix4cmp(t, scaling(-1, 1, -1))))
        return (ft_printf(msg), false);
    from = point(0, 0, 8);
    to = point(0, 0, 0);
    up = vector(0, 1, 0);
    t = view_transform(from, to, up);
    if (!(matrix4cmp(t, translation(0, 0, -8))))
        return (ft_printf(msg), false);
    from = point(1, 3, 2);
    to = point(4, -2, 8);
    up = vector(1, 1, 0);
    t = view_transform(from, to, up);
    if (!(matrix4cmp(t, matrix4(
            tup4(-0.50709, 0.50709, 0.67612, -2.36643),
            tup4(0.76772, 0.60609, 0.12122, -2.82843),
            tup4(-0.35857, 0.59761, -0.71714, 0),
            tup4(0, 0, 0, 1)))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_camera(void)
{
    char    *msg = "test_camera failed!\n";

    float   hsize;
    float   vsize;
    float   field_of_view;
    t_camera    *c;

    hsize = 160;
    vsize = 120;
    field_of_view = M_PI / 2;
    c = camera(hsize, vsize, field_of_view);
    if (!(ft_fcmp(c->hsize, 160) && ft_fcmp(c->vsize, 120)
            && ft_fcmp(c->field_of_view, M_PI / 2)
            && matrix4cmp(c->transform, identity_matrix4())))
        return (ft_printf(msg), false);
    c = camera(200, 125, M_PI / 2);
    if (!(ft_fcmp(c->pixel_size, 0.01)))
        return (ft_printf(msg), false);
    c = camera(125, 200, M_PI / 2);
    if (!(ft_fcmp(c->pixel_size, 0.01)))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_ray_for_pixel(void)
{
    char    *msg = "test_ray_for_pixel failed!\n";
    t_camera    *c;
    t_ray   r;

    c = camera(201, 101, M_PI / 2);
    r = ray_for_pixel(c, 100, 50);
    if (!(tup4cmp(r.origin, point(0, 0, 0))
        && tup4cmp(r.direction, vector(0, 0, -1))))
        return (ft_printf(msg), false);
    r = ray_for_pixel(c, 0, 0);
    if (!(tup4cmp(r.origin, point(0, 0, 0))
        && tup4cmp(r.direction, vector(0.66519, 0.33259, -0.66851))))
        return (ft_printf(msg), false);
    c->transform = multiply_matrix4(rotation_y(M_PI / 4),
                                    translation(0, -2, 5));
    r = ray_for_pixel(c, 100, 50);
    if (!(tup4cmp(r.origin, point(0, 2, -5))
        && tup4cmp(r.direction, vector(sqrt(2) / 2, 0, -(sqrt(2) / 2)))))
        return (ft_printf(msg), false);
    return (true);
}

bool    test_render(void)
{
    char    *msg = "failed!\n";

    if (!(1))
        return (ft_printf(msg), false);
    return (true);
}

/*bool    test_(void)
{
    char    *msg = "failed!\n";
    t_world     *w;
    t_camera    *c;
    t_canvas    *canvas;
    w = default_world();
    c = camera(11, 11, M_PI / 2);
    c->transform = view_transform(point(0, 0, -5),
                                point(0, 0, 0),
                                vector(0, 1, 0));
    
    if (!(1))
        return (ft_printf(msg), false);
    return (true);
}*/

void    run_tests(void)
{
    if (test_tuple() && test_point() && test_vector() 
        && test_add_tup4() && test_subtract_tup4()
        && test_negate_tup4() && test_multiply_tup4()
        && test_divide_tup4() && test_magnitude()
        && test_normalization() && test_dot()
        && test_cross() && test_color() && test_hadamard()
        && test_matrix2() && test_matrix3() && test_matrix4()
        && test_matrix4cmp() && test_multiply_matrix4()
        && test_matrix4_mult_tup4() && test_identity_matrix()
        && test_transpose_matrix4() && test_determinant2()
        && test_submatrix3() && test_submatrix4()
        && test_cofactor3() && test_cofactor4()
        && test_detetrminant3() && test_detetrminant4()
        && test_is_matrix4_invertible() && test_invert_matrix4())
        printf("All tuple and matrix operations tests passed!!\n");
    if (test_translation() && test_scaling() && test_rotation_x()
        && test_rotation_y() && test_rotation_z() && test_shearing())
        printf("All transformation tests passed!!\n");
    if (test_sphere_normal() && test_reflect() && test_lighting())
        printf("All light tests passed!!\n");
    if (test_world() && test_prepare_computations() && test_shade_hit()
        && test_color_at() && test_view_transform() && test_camera()
        && test_ray_for_pixel()/* && test_render()*/)
        printf("All scene tests passed!!\n");

}

/*void	sphere_testing()
{
	t_ray		R;
	t_sphere	*S;
	t_list		*xs;
	t_list		*xs_current;
	t_tup4		i_pt[2];
	t_list		*i;
	t_matrix4	scaling;
	int			j;

	R.origin = tup4(0, 0, -5, TPOINT);
	R.direction = tup4(0, 0, 1, TVECTOR);

	S = sphere();

	scaling = matrix4(tup4(0.5, 0, 0, 0), tup4(0, 0.5, 0, 0),
			tup4(0, 0, 0.5, 0), tup4(0, 0, 0, 1));

	set_transform(S, scaling);

	xs = intersect(S, R);

	i = NULL;
	i = hit(xs);

	xs_current = xs;
	while(xs_current)
	{
		printf("X1.t %f\n", ((t_intersection *)xs_current->content)->t);
		xs_current = xs_current->next;
	}

	if(i)
		printf("Hit : %f\n", ((t_intersection *)i->content)->t);

	j = 0;
	xs_current = xs;
	while(xs_current)
	{
		i_pt[j] = tup4((R.origin.x + ((t_intersection *)xs_current->content)->t * R.direction.x),
			(R.origin.y + ((t_intersection *)xs_current->content)->t * R.direction.y),
			(R.origin.z + ((t_intersection *)xs_current->content)->t * R.direction.z), TPOINT);
		xs_current = xs_current->next;
		j++;
	}

	printf("p1 x value: %f\n", i_pt[0].x);
	printf("p1 y value: %f\n", i_pt[0].y);
	printf("p1 z value: %f\n", i_pt[0].z);

	printf("p2 x value: %f\n", i_pt[1].x);
	printf("p2 y value: %f\n", i_pt[1].y);
	printf("p2 z value: %f\n", i_pt[1].z);

	ft_lstclear(&xs, free);

	free (S);
	free(xs);
}*/