/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:21:45 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/08 14:44:11 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	process_texture_lines(t_game *game, int *count)
{
	char	*line_with_newline;
	char	*temp_texture;
	char	*line;

	while (game->data->line)
	{
		line = ft_skipspace(game->data->line);
		if (line[0] == '1' || line[0] == ' ')
			break ;
		if (check_text_name(line))
		{
			line_with_newline = ft_strjoin(line, "\n");
			temp_texture = ft_strjoin(game->data->textures_line,
					line_with_newline);
			free(line_with_newline);
			free(game->data->textures_line);
			game->data->textures_line = temp_texture;
			(*count)++;
		}
		free(game->data->line);
		game->data->line = get_next_line(game->data->fd);
	}
	if (!game->data->line)
		return (ft_error_msg("Error no map found\n", game));
	return (0);
}
