/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:14:57 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/23 13:47:01 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math/v2i.h"
#include "menu.h"
#include "render/render.h"
#include <X11/Xlib.h>

int	key_pressed_hook(int keycode, t_vars *vars)
{
	if (keycode < 0 || keycode >= 0xFFFF)
		return (0);
	r3d_key_hook(keycode, &vars->r3d);
	menu_key(&vars->menu, vars, keycode);
	if (keycode == XK_Escape)
		vars->is_focused = false;
	vars->keys[keycode] = true;
	return (0);
}

int	key_released_hook(int keycode, t_vars *vars)
{
	if (keycode < 0 || keycode >= 0xFFFF)
		return (0);
	vars->keys[keycode] = false;
	return (0);
}

int	mouse_move_hook(int x, int y, t_vars *vars)
{
	vars->mouse_pos = (t_v2i){x, y};
	return (0);
}

int	mouse_button_pressed_hook(int btn, int _i1, int _i2, t_vars *vars)
{
	(void) _i1;
	(void) _i2;
	if (btn == 1 && !vars->is_focused)
		vars->is_focused = true;
	if (btn >= 0 && btn < 8)
		vars->buttons[btn] = true;
	return (0);
}

int	mouse_button_released_hook(int btn, int _i1, int _i2, t_vars *vars)
{
	(void) _i1;
	(void) _i2;
	if (btn >= 0 && btn < 8)
		vars->buttons[btn] = false;
	return (0);
}
