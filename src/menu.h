/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopekdas <vopekdas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:45:22 by ledelbec          #+#    #+#             */
/*   Updated: 2024/06/20 14:48:04 by vopekdas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "libft.h"
# include "mem.h"
# include "math/v2i.h"
# include "render/font.h"
# include <stdbool.h>

typedef struct s_vars	t_vars;

typedef struct s_boxi
{
	t_v2i	min;
	t_v2i	max;
}	t_boxi;

typedef void (*t_button_pressed)(t_vars *vars);

typedef struct s_button
{
	char				*label;
	t_image				*image;
	float				scale;

	t_boxi				box;
	bool				disabled;
	t_button_pressed	pressed;
}	t_button;

void	button_draw(t_button *button, t_r3d *r3d);
void	button_tick(t_button *button, t_vars *vars);

# define TEXT_EDIT_SIZE 16

typedef bool (*t_text_edit_filter)(char c);

typedef struct s_text_edit
{
	char				buffer[TEXT_EDIT_SIZE + 1];
	size_t				len;

	t_boxi				box;
	bool				disabled;
	bool				focused;

	t_text_edit_filter	filter;
}	t_text_edit;

void	text_edit_draw(t_text_edit *text_edit, t_r3d *r3d, t_vars *vars);
void	text_edit_tick(t_text_edit *text_edit, t_vars *vars);

void	text_edit_key(t_text_edit *text_edit, int c);

typedef struct s_menu_img
{
	t_image	*image;
	t_v2i	pos;
	float	scale;
}	t_menu_img;

void	img_draw(t_menu_img *img, t_r3d *r3d);

typedef enum e_state
{
	STATE_MAIN,
	STATE_MULTIPLAYER
}	t_state;

typedef struct s_menu
{
	t_state		state;
	bool		already_pressed;

	t_button	singleplayer;
	t_button	multiplayer;

	// Multiplayer
	t_button	host;
	t_button	join;

	t_menu_img	ip_img;
	t_text_edit	ip;

	t_menu_img	name_img;
	t_text_edit	name;
}	t_menu;

void	menu_init(t_menu *menu, t_r3d *r3d, t_alloc_table *at);
void	menu_draw(t_menu *menu, t_r3d *r3d, t_vars *vars);
void	menu_tick(t_menu *menu, t_vars *vars);

void	menu_key(t_menu *menu, t_vars *vars, int c);

bool	mouse_click_over(t_vars *vars, t_boxi box);

#endif