/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azibechi <azibechi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:37:11 by azibechi          #+#    #+#             */
/*   Updated: 2025/12/15 19:29:40 by azibechi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_player_provisional(t_game *game)
{
    // 1. Posición inicial (centro de la casilla 5,5)
    game->player.pos.x = 5.5;
    game->player.pos.y = 5.5;

    // 2. Vector de Dirección: Mirando al NORTE
    // En coordenadas de pantalla, Y disminuye hacia arriba.
    game->player.dir.x = 0;
    game->player.dir.y = -1;

    // 3. Vector del Plano de Cámara (FOV)
    // Debe ser perpendicular a la dirección. Longitud 0.66 da ~66 grados de FOV.
    // Si Dir es (0, -1), el Plano es (0.66, 0).
    game->player.plane.x = 0.66;
    game->player.plane.y = 0;
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_memset(game->image->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
}

void	ft_hooks(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

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
	mlx_loop_hook(game->mlx, &ft_hooks, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
	init_player_provisional(game);
	return (0);
}
