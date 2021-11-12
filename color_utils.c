/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:03:11 by lajudy            #+#    #+#             */
/*   Updated: 2021/11/12 21:44:10 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_r(int trgb)
{
	return (trgb >> 16);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & ((1 << 8) - 1));
}

int	get_b(int trgb)
{
	return ((trgb >> 0) & ((1 << 8) - 1));
}

int	gradient(int color, int color1, float n_steps, int n)
{
	float	r_diff;
	float	g_diff;
	float	b_diff;
	int		result;

	r_diff = get_r(color1) - get_r(color);
	g_diff = get_g(color1) - get_g(color);
	b_diff = get_b(color1) - get_b(color);
	r_diff = get_r(color) + r_diff / n_steps * n;
	g_diff = get_g(color) + g_diff / n_steps * n;
	b_diff = get_b(color) + b_diff / n_steps * n;
	result = r_diff;
	result = (result << 8) + g_diff;
	result = (result << 8) + b_diff;
	return (result);
}
