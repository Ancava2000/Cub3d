/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:52:14 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/08 14:50:16 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_format(char **textures)
{
	int		i;
	char	*line;

	i = 0;
	while (textures[i])
	{
		line = textures[i];
		if (*line == 'F' || *line == 'C')
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		{
			line += 2;
			while (ft_isspace(*line))
				line++;
			if (line[0] != '.' || line[1] != '/' || line[2] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

void	count_textures(char	*line, t_count *count)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		count->no++;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		count->so++;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		count->ea++;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		count->we++;
	else if (ft_strncmp(line, "C ", 2) == 0)
		count->c++;
	else if (ft_strncmp(line, "F ", 2) == 0)
		count->f++;
}

int	textures_split(t_game *game)
{
	char	**textures_split;
	int		i;

	i = 0;
	game->data->textures_split = ft_split(game->data->textures_line, '\n');
	textures_split = game->data->textures_split;
	while (textures_split[i])
	{
		count_textures(textures_split[i], game->data->count);
		i++;
	}
	if (game->data->count->no != 1 || game->data->count->so != 1
		|| game->data->count->ea != 1 || game->data->count->we != 1
		|| game->data->count->c != 1 || game->data->count->f != 1)
		return (ft_error_msg("Error with duplicates", game));
	if (check_format(textures_split))
		return (ft_error_msg("Error with texture format", game));
	return (0);
}

int	check_text_name(char *line)
{
	if (!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2)
		|| !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "NO", 2)
		|| !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

int	parse_textures(t_game *game)
{
	int	count;

	count = 0;
	if (process_texture_lines(game, &count))
		return (1);
	if (count != 6)
		return (ft_error_msg("Error with number of textures\n", game));
	if (textures_split(game))
		return (1);
	return (0);
}

/*
int	parse_textures(t_game *game)
{
	int		count;
	char	*temp_texture;
	char	*line_with_newline;
	char	*line;

	count = 0;
	while (game->data->line)
	{
		line = ft_skipspace(game->data->line);
		if (line[0] == '1' || line[0] == ' ')
			break ;
		if (check_text_name(line))
		{
			line_with_newline = ft_strjoin(line, "\n");
			temp_texture = ft_strjoin(game->data->textures_line, line_with_newline);
			free(line_with_newline);
			free(game->data->textures_line);
			game->data->textures_line = temp_texture;
			count++;
		}
		free(game->data->line);
		game->data->line = get_next_line(game->data->fd);
	}
	if (!game->data->line)
		return (ft_error_msg("Error no map found\n", game));
	if (count != 6)
		return (ft_error_msg("Error with number of textures\n", game));
	if (textures_split(game))
		return (1);
	return (0);
}
*/
