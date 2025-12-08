/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:38:07 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/08 12:33:17 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_parse(t_game *game)
{
	game->data->fd = -1;
	game->data->line = NULL;
	game->data->map_array = NULL;
	game->data->textures_line = ft_strdup("");
	game->data->textures_split = NULL;
	game->data->count = ft_calloc(1, sizeof(t_count));
	if (!game->data->count)
		return (ft_error_msg("Failed to allocate count\n", game));
	game->texture = NULL;
	return (0);
}

int	check_args(int ac, char **av, t_game *game)
{
	char	*extension;

	if (ac != 2)
		return (ft_error_msg("Only two arguments: ./cub3d + *.cub\n", game));
	extension = ft_strrchr(av[1], '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
		return (ft_error_msg("Not the correct extension. It must be .cub\n",
				game));
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = ft_calloc(1, sizeof (t_game));
	if (!game)
		return (ft_error_msg("Error allocating memory for game\n", game));
	game->data = ft_calloc(1, sizeof(t_data));
	if (!game->data)
		return (ft_error_msg("Error allocating memory for data\n", game));
	if (init_parse(game))
		return (-1);
	if (check_args(ac, av, game))
		return (-1);
	if (parse(av, game))
		return (-1);
	free_game(game);
	return (0);
}
