/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr2dsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:37:22 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/11 12:47:25 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arr2dsize(void **arr2d)
{
	int	size;

	size = 0;
	if (!arr2d)
		return (0);
	while (*arr2d)
	{
		size++;
		arr2d++;
	}
	return (size);
}