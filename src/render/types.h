/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:19:15 by ledelbec          #+#    #+#             */
/*   Updated: 2024/03/20 21:20:37 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/*
 * Some various types for the render engine.
 */

typedef union s_color
{
	unsigned int		raw;
	struct
	{
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
		unsigned char	t;
	};
}	t_color;

t_color	hex(unsigned int hex);
t_color	rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char t);
t_color	rgbaf(float r, float g, float b, float t);
t_color	grayscalef(float f);
t_color	color_scale(t_color col, float f);

#endif