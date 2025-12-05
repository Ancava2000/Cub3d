/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:51:38 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/05 14:38:24 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	read_map(char *av, t_game *game)
{
	game->data->fd = open(av, O_RDONLY);
	if (game->data->fd == NULL)
	{
		close(game->data->fd);
		return (ft_error_msg("Error opening map\n", game));
	}
	game->data->line = get_next_line(game->data->fd);
	if (game->data->line == NULL)
		return (ft_error_msg("Error opening map\n", game));
	close(game->data->fd);
	return (0);
}

int	parse(int ac, char **av, t_game *game)
{
	if (read_map(av[1], game))
		return (-1);
	if (parse_textures(game))
		return (-1);
	if (parse_colors(game))
		return (-1);
	if (parse_map())
		return (-1);
	if (list_textures())
		return (-1);
	if (list_colors())
		return (-1);
	return (0);
}
