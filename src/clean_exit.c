/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:29:49 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/09/05 11:37:09 by joamonte         ###   ########.fr       */
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
