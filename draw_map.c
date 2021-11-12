/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:42:37 by lajudy            #+#    #+#             */
/*   Updated: 2021/11/13 00:24:56 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	abs_max(float a, float b)
{
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	if (a > b)
		return (a);
	return (b);
}

void	draw_pixel(t_map *map, int x, int y, int color)
{
	char	*dst;

	dst = map->addr + (y * map->bytes_per_line + x * (map->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	make_projection(t_map *map, t_line *line)
{
	if (map->zoom_scale != 0)
		line->z *= map->zoom / map->zoom_scale;
	if (map->zoom_scale != 0)
		line->z1 *= map->zoom / map->zoom_scale;
	if (map->projection == 1)
		make_projection1(map, line);
	if (map->projection == 2)
		make_projection2(map, line);
	if (map->projection == 3)
		make_projection3(map, line);
}

void	draw_line(t_map *map, t_line line, int color)
{
	float		x_step;
	float		y_step;
	float		max;
	float		n_steps;
	int			i;

	make_projection(map, &line);
	line_coord_prepare(map, &line, color);
	x_step = line.x1 - line.x;
	y_step = line.y1 - line.y;
	max = abs_max(x_step, y_step);
	x_step /= max;
	y_step /= max;
	n_steps = max / abs_max (x_step, y_step);
	i = 0;
	while ((int)(line.x - line.x1) || (int)(line.y - line.y1))
	{
		if (line.x > 0 && line.y > 0 && line.x < WIDTH - 1
			&& line.y < HEIGHT - 1)
			draw_pixel(map, line.x, line.y,
				gradient(line.color, line.color1, (int)n_steps, i++));
		line.x += x_step;
		line.y += y_step;
	}
}

void	draw_map(t_map *map)
{
	int		x;
	int		y;
	t_line	line;

	if (map->mlx_ptr == NULL)
	{
		map->mlx_ptr = mlx_init();
		map->window_ptr = mlx_new_window(map->mlx_ptr, WIDTH, HEIGHT, TITLE);
		map->img = NULL;
	}
	map->img = mlx_new_image(map->mlx_ptr, WIDTH, HEIGHT);
	map->addr = mlx_get_data_addr(map->img, &map->bits_per_pixel,
			&map->bytes_per_line, &map->endian);
	y = 0;
	while (y < map->height - 1)
	{
		x = -1;
		while (++x < map->width - 1)
			draw_grid(map, &line, x, y);
		y++;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->window_ptr, map->img, 0, 0);
	mlx_destroy_image(map->mlx_ptr, map->img);
}
