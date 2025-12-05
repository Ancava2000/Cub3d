/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:44:52 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/05 12:57:10 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <ctype.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

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

typedef struct s_texture
{
	char		*name;
	char		*path;
	t_texture	*next;
}	t_texture;

// struct all data (*map, *map_copy, **map, all textures, F parseo (color), c parseo (color), floor color, ceiling color,)
typedef struct s_data
{
	int			fd;
	char		*line;
	char		*line_copy;
	char		**map_array;
	char		*textures_line;
	char		**textures_split;
	t_count		*count;
	char		**f_color;
	char		**c_color;
	t_color		floor;
	t_color		ceiling;
}				t_data;

// struct game with all structs (all data (textures paths), player, movements, all images, image mlx, mlx, window)
typedef struct s_game
{
	t_data		*data;   // to create a canvas
	t_texture	*texture;
	t_image		image_no;
	t_image		image_so;
	t_image		image_we;
	t_image		image_ea;
	t_player	player;
	t_moves		movements;
	t_ray		raycasting;
	void		*mlx;
	void		*window;
	void		*image;
}	t_game;


int	ft_error_msg(char *str, t_game *game);
int	check_args(int ac, char **av, t_game *game);

#endif