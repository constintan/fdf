/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:22:10 by lajudy            #+#    #+#             */
/*   Updated: 2021/11/13 00:24:20 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	coord_prepare_horizontal(t_line *line, float x, float y, float z)
{
	line->x = x;
	line->y = y;
	line->z = z;
	line->x1 = x + 1;
	line->y1 = y;
	line->z1 = line->z;
	line->color1 = line->color;
}

void	coord_prepare_vertical(t_line *line, float x, float y)
{
	line->x1 = x;
	line->y1 = y + 1;
	line->z1 = line->z;
	line->color1 = line->color;
}

void	line_coord_prepare(t_map *map, t_line *line, int color)
{
	line->x *= map->zoom;
	line->y *= map->zoom;
	line->x1 *= map->zoom;
	line->y1 *= map->zoom;
	line->x += map->x_shift;
	line->y += map->y_shift;
	line->x1 += map->x_shift;
	line->y1 += map->y_shift;
	if (map->color_scheme % 2 == 0)
	{
		line->color = color;
		line->color1 = color;
	}
}

int	choose_color(t_line *line)
{
	if (line->z1 > 0 || line->z > 0)
		return (0x00FF0000);
	if (line->z1 < 0 || line->z < 0)
		return (0x000000FF);
	return (0x00FFFFFF);
}

void	draw_grid(t_map *map, t_line *line, int x, int y)
{
	int	color;

	line->color = map->colors[y][x];
	coord_prepare_horizontal(line, x, y, map->z[y][x]);
	if (x + 1 < map->width - 1)
	{
		line->z1 = map->z[y][x + 1];
		line->color1 = map->colors[y][x + 1];
	}
	color = choose_color(line);
	draw_line(map, *line, color);
	line->color = map->colors[y][x];
	coord_prepare_vertical(line, x, y);
	if (y + 1 < map->height - 1)
	{
		line->z1 = map->z[y + 1][x];
		line->color1 = map->colors[y + 1][x];
	}
	color = choose_color(line);
	draw_line(map, *line, color);
}
