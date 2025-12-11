/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azibechi <azibechi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:37:11 by azibechi          #+#    #+#             */
/*   Updated: 2025/12/11 20:50:02 by azibechi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	
	return (0);
}
