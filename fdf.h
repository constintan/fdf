/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:28:49 by lajudy            #+#    #+#             */
/*   Updated: 2021/11/13 00:46:49 by lajudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <unistd.h>
# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <math.h>

# define WIDTH 1500
# define HEIGHT 1300
# define DEFAULT_COLOR 0x00FFFFFF
# define DEFAULT_COLOR_SCHEME 1
# define TITLE "FdF"
# define START_ZOOM 30
# define ZOOM_STEP 1
# define ZOOM_COMPENSATE 0
# define START_SHIFT_X WIDTH / 2
# define START_SHIFT_Y HEIGHT / 3
# define SHIFT_STEP 30
# define ANGLE1 0.8
# define ANGLE2 0.8
# define START_ROTATION 0
# define START_PROJECTION 1

typedef struct s_map
{
	void	*mlx_ptr;
	void	*window_ptr;
	void	*img;
	int		width;
	int		height;
	int		**z;
	int		**colors;
	int		color_scheme;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		bytes_per_line;
	int		endian;
	int		zoom;
	int		zoom_scale;
	int		x_shift;
	int		y_shift;
	float	angle1;
	float	angle2;
	float	rotation;
	int		projection;
}	t_map;

typedef struct s_line
{
	float	x;
	float	y;
	float	z;
	int		color;
	float	x1;
	float	y1;
	float	z1;
	int		color1;
}	t_line;

//libft.c
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);

//get_next_line.c
char	*get_next_line(int fd);

//map_init.c
t_map	*map_init(char *file_name);

//map_init2.c
void	str_to_numbers_colors(char *str, int *numbers, int n);
int		**fill_colors(int fd, t_map *map);
void	clear_all(t_map *map);

//ft_split.c
char	**ft_split(char const *s, char c);
int		splited_size(char **words);
void	free_after_split(char **argv);

//ft_atoi.c
int		ft_atoi(const char *str);
int		ft_atoi_hex(const char *str);

//draw_map.c
void	draw_map(t_map *map);
void	draw_line(t_map *map, t_line line, int color);

////draw_map_utils.c
void	coord_prepare_horizontal(t_line *line, float x, float y, float z);
void	coord_prepare_vertical(t_line *line, float x, float y);
void	line_coord_prepare(t_map *map, t_line *line, int color);
void	draw_grid(t_map *map, t_line *line, int x, int y);

//color_utils.c
int		gradient(int color, int color1, float n_steps, int n);

//draw_projections.c
void	make_projection1(t_map *map, t_line *line);
void	make_projection2(t_map *map, t_line *line);
void	make_projection3(t_map *map, t_line *line);

#endif