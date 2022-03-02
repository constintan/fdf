/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:25:31 by lajudy            #+#    #+#             */
/*   Updated: 2022/03/02 22:09:49 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(int keycode, t_map *map)
{
	(void) keycode;
	(void) map;
	exit (0);
}

/*
up 126
down 125
left 123
right 124
pgup 116
pgdown 121
*/
int	key_hook2(int keycode, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keycode == 116)
		map->angle1 += 0.1;
	if (keycode == 121)
		map->angle1 -= 0.1;
	if (keycode == 115)
		map->angle2 += 0.1;
	if (keycode == 119)
		map->angle2 -= 0.1;
	if (keycode == 24)
		map->zoom_scale += ZOOM_STEP;
	if (keycode == 27 && map->zoom_scale - 1 >= 0)
		map->zoom_scale -= ZOOM_STEP;
	if (keycode == 8)
		map->color_scheme++;
	draw_map(map);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_map	*map;

	if (keycode == 116 || keycode == 121 || keycode == 115 || keycode == 119
		|| keycode == 24 || keycode == 27 || keycode == 8)
		return (key_hook2(keycode, param));
	map = (t_map *)param;
	if (keycode == 30)
		map->rotation += 0.1;
	if (keycode >= 18 && keycode <= 20)
		map->projection = keycode - 17;
	if (keycode == 33)
		map->rotation -= 0.1;
	if (keycode == 125 || keycode == 1)
		map->y_shift += SHIFT_STEP;
	if (keycode == 126 || keycode == 13)
		map->y_shift -= SHIFT_STEP;
	if (keycode == 124 || keycode == 2)
		map->x_shift += SHIFT_STEP;
	if (keycode == 123 || keycode == 0)
		map->x_shift -= SHIFT_STEP;
	if (keycode == 53)
		close_window(keycode, map);
	draw_map(map);
	return (0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_map	*map;

	(void)x;
	(void)y;
	map = (t_map *)param;
	if (button == 4)
		map->zoom += ZOOM_STEP;
	if (button == 5 && map->zoom - ZOOM_STEP > 0)
		map->zoom -= ZOOM_STEP;
	draw_map(map);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	(void)argv;
	if (argc == 1)
		ft_putstr_fd("Error! Pass file name as an argument!\n", 2);
	if (argc > 2)
		ft_putstr_fd("Error! Wrong number of arguments!\n", 2);
	if (argc == 2)
	{
		map = map_init(argv[1]);
		if (map != NULL)
		{
			draw_map(map);
			mlx_hook(map->window_ptr, 17, 0, close_window, map);
			mlx_hook(map->window_ptr, 2, 1L << 0, key_hook, map);
			mlx_mouse_hook (map->window_ptr, mouse_hook, map);
			mlx_loop(map->mlx_ptr);
		}
		else
			ft_putstr_fd("Error! Something is wrong with reading a file!\n", 2);
	}
}
