/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:05:23 by lajudy            #+#    #+#             */
/*   Updated: 2021/11/13 00:38:22 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	str_to_numbers(char *str, int *numbers, int n)
{
	char	**words;
	int		i;
	int		nwords;

	words = ft_split(str, ' ');
	nwords = splited_size(words);
	i = 0;
	while (i < n)
	{
		if (i < nwords)
			numbers[i] = ft_atoi(words[i]);
		else
			numbers[i] = 0;
		i++;
	}
	free_after_split(words);
}

int	**fill_z_axis(int fd, t_map *map)
{
	int		**result;
	int		y;
	char	*str;

	result = (int **)malloc(sizeof(int *) * map->height);
	if (result == NULL)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		result[y] = (int *)malloc(sizeof(int) * map->width);
		if (result[y] == NULL)
		{
			while (--y >= 0)
				free(result[y]);
			free(result);
			return (NULL);
		}
		str = get_next_line(fd);
		str_to_numbers(str, result[y], map->width);
		free(str);
		y++;
	}
	return (result);
}

t_map	*count_xy(int fd)
{
	char	*str;
	char	**numbers;
	int		x;
	int		y;
	t_map	*map;

	x = 0;
	y = 0;
	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	str = get_next_line(fd);
	numbers = ft_split(str, ' ');
	x = splited_size(numbers);
	map->width = x;
	free_after_split(numbers);
	while (str)
	{
		y++;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	map->height = y;
	return (map);
}

int	map_start_properies(char *file_name, t_map *map)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (-1);
	map->z = fill_z_axis(fd, map);
	close(fd);
	if (map->z == NULL)
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (-1);
	map->colors = fill_colors(fd, map);
	close(fd);
	if (map->colors == NULL)
		return (-1);
	map->mlx_ptr = NULL;
	map->zoom = START_ZOOM;
	map->x_shift = START_SHIFT_X;
	map->y_shift = START_SHIFT_Y;
	map->angle1 = ANGLE1;
	map->angle2 = ANGLE2;
	map->zoom_scale = ZOOM_COMPENSATE;
	map->color_scheme = DEFAULT_COLOR_SCHEME;
	return (0);
}

t_map	*map_init(char *file_name)
{
	int		fd;
	t_map	*map;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = count_xy(fd);
	close(fd);
	if (map == NULL)
		return (NULL);
	if (map_start_properies(file_name, map) < 0)
	{
		free(map);
		return (NULL);
	}
	map->rotation = START_ROTATION;
	map->projection = START_PROJECTION;
	return (map);
}
