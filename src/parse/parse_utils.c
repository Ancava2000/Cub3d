/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:21:45 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/10 16:52:25 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Proccess the line, skipping the spaces or tabs and adding a '\n'.
// When the line starts with the texture name it is added to the texture_line via a temp variable.
// If a 1 isn't found, it shows the no map error.
int	process_texture_lines(t_game *game, int *count)
{
	char	*temp_texture;
	char	*line; // line without spaces at the start

	while (game->data->line)
	{
		line = ft_skipspace(game->data->line);
		if (line[0] == '1' || line[0] == ' ')
			break ;
		if (check_text_name(line))
		{
			temp_texture = ft_strjoin(game->data->textures_line,
					line);
			free(game->data->textures_line);
			game->data->textures_line = temp_texture;
			(*count)++;
		}
		free(game->data->line);
		game->data->line = get_next_line(game->data->fd);
	}
	if (!game->data->line)
		return (ft_error_msg("Error, no map found\n", game));
	return (0);
}
