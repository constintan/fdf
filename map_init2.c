/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 21:33:25 by lajudy            #+#    #+#             */
/*   Updated: 2021/11/13 00:56:07 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	str_to_numbers_colors(char *str, int *numbers, int n)
{
	char	**words;
	int		i;
	int		nwords;
	char	*ptr;

	words = ft_split(str, ' ');
	nwords = splited_size(words);
	i = 0;
	while (i < n)
	{
		ptr = ft_strchr(words[i], ',');
		if (ptr != NULL)
		{
			ptr++;
			numbers[i] = ft_atoi_hex(ptr);
		}
		else
			numbers[i] = DEFAULT_COLOR;
		i++;
	}	
	free_after_split(words);
}

int	**fill_colors(int fd, t_map *map)
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
		str_to_numbers_colors(str, result[y], map->width);
		free(str);
		y++;
	}
	return (result);
}

void	clear_all(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		free(map->z[y]);
		free(map->colors[y]);
		y++;
	}
	free(map->z);
	free(map->colors);
}
