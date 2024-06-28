/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:41:24 by vopekdas          #+#    #+#             */
/*   Updated: 2024/06/28 19:03:00 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	close_hook(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
}

void	game_loop(t_vars *vars)
{
	mlx_do_key_autorepeatoff(vars->mlx);
	mlx_loop(vars->mlx);
	mlx_do_key_autorepeaton(vars->mlx);
	ft_free(vars, &vars->at);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}
