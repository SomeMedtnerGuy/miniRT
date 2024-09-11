/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:29:49 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/10 21:09:06 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	clean_exit(t_root *r, int exit_code)
{
	mlx_destroy_image(r->mlx, r->canvas->img);
	free(r->canvas);
	mlx_destroy_window(r->mlx, r->win);
	mlx_destroy_display(r->mlx);
	free(r->mlx);
	exit(exit_code);
	return (0);
}

void	exit_with_msg(char *msg, t_root *r, int exit_code)
{
	ft_putstr_fd(msg, 2);
	clean_exit(r, exit_code);
}