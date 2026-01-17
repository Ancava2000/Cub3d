/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   mlx_init.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: azibechi <azibechi@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/12/11 17:37:11 by azibechi		  #+#	#+#			 */
/*   Updated: 2026/01/14 15:53:34 by azibechi		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Init all the variables necessary for the raycasting and movement:
// Direction where the player is looking, camera plane
// (width of the player's field of vision)
// and replace the letter(N, S, W, E) to 0
static void	init_player(t_game *game)
{
	int	x;
	int	y;

	game->player.dir.x = 0;
	game->player.dir.y = 0;
	if (game->player.dir_name == 'N')
		game->player.dir.y = -1;
	if (game->player.dir_name == 'S')
		game->player.dir.y = 1;
	if (game->player.dir_name == 'E')
		game->player.dir.x = 1;
	if (game->player.dir_name == 'W')
		game->player.dir.x = -1;
	game->player.plane.x = -game->player.dir.y * 0.66;
	game->player.plane.y = game->player.dir.x * 0.66;
//	printf("\nDEBUG: Player Pose: x=%f, y=%f\n", game->player.pos.x, game->player.pos.y);
	x = (int)game->player.pos.x;
	y = (int)game->player.pos.y;
	game->data->map_array[y][x] = '0';
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_memset(game->image->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	raycasting(game);
}

void	load_game_textures(t_game *game)
{
	t_texture	*tmp;
	char		*msg;

	tmp = game->texture;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "NO", 2))
			game->tex_north = mlx_load_png(tmp->path);
		else if (!ft_strncmp(tmp->name, "SO", 2))
			game->tex_south = mlx_load_png(tmp->path);
		else if (!ft_strncmp(tmp->name, "WE", 2))
			game->tex_west = mlx_load_png(tmp->path);
		else if (!ft_strncmp(tmp->name, "EA", 2))
			game->tex_east = mlx_load_png(tmp->path);
		tmp = tmp->next;
	}
	if (!game->tex_north || !game->tex_south
		|| !game->tex_west || !game->tex_east)
	{
		msg = "Error: Could not load all textures (Check paths/PNG format)\n";
		ft_error_msg(msg, game);
		exit(1);
	}
}

// Init game: window, image, player and textures.
// Loop: keys, game and when close.
int	init_engine(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!game->mlx)
		return (ft_error_msg("mlx_init failed\n", game));
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return (ft_error_msg("mlx_new_image failed\n", game));
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
		return (ft_error_msg("mlx_image_to_window failed\n", game));
	init_player(game);
	load_game_textures(game);
	mlx_loop_hook(game->mlx, &ft_hooks, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_close_hook(game->mlx, &close_hook, game);
	mlx_loop(game->mlx);
	free_game(game);
	return (0);
}
