/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:16:02 by lajudy            #+#    #+#             */
/*   Updated: 2021/11/13 00:22:47 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//main
void	make_projection1(t_map *map, t_line *line)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = line->x;
	tmp_y = line->y;
	line->x = tmp_x * cos(map->rotation) - tmp_y * sin(map->rotation);
	line->y = tmp_x * sin(map->rotation) + tmp_y * cos(map->rotation);
	line->x = (line->x - line->y) * cos(map->angle1);
	line->y = (line->x + line->y) * sin(map->angle2) - line->z;
	tmp_x = line->x1;
	tmp_y = line->y1;
	line->x1 = tmp_x * cos(map->rotation) - tmp_y * sin(map->rotation);
	line->y1 = tmp_x * sin(map->rotation) + tmp_y * cos(map->rotation);
	line->x1 = (line->x1 - line->y1) * cos(map->angle1);
	line->y1 = (line->x1 + line->y1) * sin(map->angle2) - line->z1;
}

//front
void	make_projection2(t_map *map, t_line *line)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = line->x;
	tmp_y = line->y;
	line->x = tmp_x * cos(map->rotation) - tmp_y * sin(map->rotation);
	line->y = tmp_x * sin(map->rotation) + tmp_y * cos(map->rotation);
	line->y = -line->z;
	tmp_x = line->x1;
	tmp_y = line->y1;
	line->x1 = tmp_x * cos(map->rotation) - tmp_y * sin(map->rotation);
	line->y1 = tmp_x * sin(map->rotation) + tmp_y * cos(map->rotation);
	line->y1 = -line->z1;
}

//birdview
void	make_projection3(t_map *map, t_line *line)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = line->x;
	tmp_y = line->y;
	line->x = (line->x - line->y) * cos(map->angle1);
	line->y = (line->x + line->y) * sin(map->angle2) - line->z;
	line->x = tmp_x * cos(map->rotation) - tmp_y * sin(map->rotation);
	line->y = tmp_x * sin(map->rotation) + tmp_y * cos(map->rotation);
	tmp_x = line->x1;
	tmp_y = line->y1;
	line->x1 = (line->x1 - line->y1) * cos(map->angle1);
	line->y1 = (line->x1 + line->y1) * sin(map->angle2) - line->z1;
	line->x1 = tmp_x * cos(map->rotation) - tmp_y * sin(map->rotation);
	line->y1 = tmp_x * sin(map->rotation) + tmp_y * cos(map->rotation);
}
