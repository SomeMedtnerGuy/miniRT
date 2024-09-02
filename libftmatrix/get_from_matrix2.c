/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_from_matrix2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:41:22 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/02 10:27:47 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmatrix.h"

float	determinant2(t_matrix2 a)
{
	return (a.e[0][0] * a.e[1][1] - a.e[0][1] * a.e[1][0]);
}
