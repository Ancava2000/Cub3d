/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:37:11 by azibechi          #+#    #+#             */
/*   Updated: 2025/12/12 00:29:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}

/* void	game_loop(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
} */

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
	mlx_key_hook(game->mlx, &ft_key_hook, game);
//	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}
