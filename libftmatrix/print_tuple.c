/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tuple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:16:02 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/08/31 14:21:43 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftmatrix.h"

void	print_tup3(t_tup3 a, bool cast_to_int)
{
	if (cast_to_int)
	{
		printf("| %i | %i | %i |\n",
			(int)a.e[0], (int)a.e[1], (int)a.e[2]);
	}
	else
		printf("| %f | %f | %f |\n", a.e[0], a.e[1], a.e[2]);
}

void	print_tup4(t_tup4 a, bool cast_to_int)
{
	if (cast_to_int)
	{
		printf("| %i | %i | %i | %i |\n",
			(int)a.x, (int)a.y, (int)a.z, (int)a.w);
	}
	else
		printf("| %f | %f | %f | %f |\n", a.x, a.y, a.z, a.w);
}
