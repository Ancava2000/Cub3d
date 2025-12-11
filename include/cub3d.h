/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:44:52 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/11 18:03:40 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <ctype.h>
# include <stdio.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

// For the mlx
# define TITLE "cub3D"
# define WIDTH 1920
# define HEIGHT 1080

// struct player (position(x y), rot speed, move speed, direction(x y), camera x y)
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir;
	double	actul_rot;
	double	rot_speed;
	double	move_speed;
}			t_player;

// struct movements player (w a s d, left and rigth rotation)
typedef struct s_moves
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	rigth;
}			t_moves;

// struct raycasting (ray direction, x camera coordenate(calculate vector of the direction), )
typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	camera_x;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
}			t_ray;

// images void * width and height(to use mlx_file_to_image)
typedef struct s_image
{
	void	*ptr;   // stores reference to image
	int		width;
	int		height;
}			t_image;

// struct to count textures
typedef	struct s_count
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_count;

// struct color (r, g, b of floor and ceiling)
typedef struct s_color
{
	int r;
	int g;
	int b;
}		t_color;

// struct for textures: name(NO, SO,...) and path(./...)
typedef struct s_texture t_texture;

typedef struct s_texture
{
	char		*name;
	char		*path;
	t_texture	*next;
}	t_texture;

// struct all data of parse(*map, *map_copy, **map, all textures, F parseo (color), c parseo (color), floor color, ceiling color,)
typedef struct s_data
{
	int			fd; // to save the .cub
	char		*line; // each line of the .cub with get_next_line
	char		*line_copy;
	char		**map_array;
	char		*textures_line; // a string with all the textures
	char		**textures_split; // all the textures split by '\0'
	t_count		*count;
}				t_data;

// struct game with all structs (all data (textures paths), player, movements, all images, image mlx, mlx, window)
typedef struct s_game
{
	t_data		*data;
	t_texture	*texture;
	t_color		floor;
	t_color		ceiling;
	t_image		image_no;
	t_image		image_so;
	t_image		image_we;
	t_image		image_ea;
	t_player	player;
	t_moves		movements;
	t_ray		raycasting;
	void		*mlx;
	void		*window;
	void		*image; // to create a canvas
}	t_game;

// PARSE GENERAL
int		parse(char **av, t_game *game);
int		parse_textures(t_game *game);
int		parse_colors(t_game *game);
int		process_texture_lines(t_game *game, int *count);
int		check_text_name(char *line);
int		check_open_path(char *path);

// PARSE CREATE LISTS
int		list_textures(t_game *game);
int		list_colors(t_game *game);

// ERRORS AND FREE
int		ft_error_msg(char *str, t_game *game);
void	free_game(t_game *game);
void	free_array(char **str);

#endif