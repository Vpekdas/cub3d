/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:35:48 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/28 18:37:18 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

bool init_mlx_settings(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		ft_putstr_fd(RED"Error\nMLX pointed returned NULL\n"RESET, 2);
		ft_free(vars, &vars->at);
		return (false);
	}
	vars->win = mlx_new_window(vars->mlx, 1280, 720, "cub3D");
	if (!vars->win)
	{
		ft_putstr_fd(RED"Error\nFailed to create the windows\n"RESET, 2);
		ft_free(vars, &vars->at);
		return (false);
	}
	return (true);
}
