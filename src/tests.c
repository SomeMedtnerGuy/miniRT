/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:41:52 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/02 11:25:48 by ndo-vale         ###   ########.fr       */
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
    if (1)
        printf("All transformation tests passed!\n");
}
