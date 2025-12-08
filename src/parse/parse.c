/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:51:38 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/08 12:25:44 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	read_map(char *av, t_game *game)
{
	game->data->fd = open(av, O_RDONLY);
	if (game->data->fd == -1)
	{
		close(game->data->fd);
		return (ft_error_msg("Error opening map\n", game));
	}
	game->data->line = get_next_line(game->data->fd);
	if (game->data->line == NULL)
		return (ft_error_msg("Error opening map\n", game));
	return (0);
}

int	parse(char **av, t_game *game)
{
	if (read_map(av[1], game))
		return (-1);
	if (parse_textures(game))
		return (-1);
	if (parse_colors(game))
		return (-1);
	close(game->data->fd);
//	if (parse_map())
//		return (-1);
	if (list_textures(game))
		return (-1);
	if (list_colors(game))
		return (-1);
	return (0);
}
