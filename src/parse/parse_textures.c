/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:52:14 by acarro-v          #+#    #+#             */
/*   Updated: 2025/11/27 15:52:15 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_text_name(char *line)
{
	while (isspace(*line))
		line++;
	if (!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2) ||
			!ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "NO", 2) ||
			!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

int	parse_textures(t_game *game)
{
	int	count;

	count = 0;
	while (game->data->line && game->data->line[0] != '1' && game->data->line[0] != ' ')
	{
		if (check_text_name(game->data->line))
		{
			count++;
		}
		free(game->data->line);
		game->data->line = get_next_line(game->data->fd);
	}
	if (count !=6)
		return (ft_error_msg("Error with number of textures\n", game));
	if (duplicate(game))
		return (ft_error_msg("There are duplicated textures\n", game));
	return (0);
}
