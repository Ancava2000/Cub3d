/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:52:58 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/14 16:28:15 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	count_height(t_game *game)
{
	char	*line;
	int		flag;

	flag = 0;
	line = ft_strdup(game->data->line);
	while (line)
	{
		if (is_empty_line(line))
			flag = 1;
		else if (flag)
		{
			free(line);
			return (ft_error_msg("Error: empty line in map\n", game));
		}
		else
			game->data->map_height++;
		free(line);
		line = get_next_line(game->data->fd);
	}
	if (flag)
		return (ft_error_msg("Error: empty line at end of map\n", game));
	return (0);
}

int	reopen(t_game *game, char *map_path)
{
	char	*trimmed;

	close(game->data->fd);
	game->data->fd = open(map_path, O_RDONLY);
	if (game->data->fd == -1)
		return (ft_error_msg("Error reopening map\n", game));
	if (game->data->line)
		free(game->data->line);
	game->data->line = get_next_line(game->data->fd);
	while (game->data->line)
	{
		trimmed = ft_skipspace(game->data->line);
		if (trimmed[0] == '1' || trimmed[0] == ' ')
			break ;
		free(game->data->line);
		game->data->line = get_next_line(game->data->fd);
	}
	return (0);
}

void	fill_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->data->map_height && game->data->line)
	{
		game->data->map_array[i] = ft_strdup(game->data->line);
		free(game->data->line);
		game->data->line = get_next_line(game->data->fd);
		i++;
	}
	game->data->map_array[i] = NULL;
}

int	parse_map(t_game *game, char *map_path)
{
	if (count_height(game))
		return (1);
	if (reopen(game, map_path))
		return (1);
	game->data->map_array = malloc((game->data->map_height + 1)
			* sizeof(char *));
	if (!game->data->map_array)
		return (ft_error_msg("Error allocating memory for map_array\n", game));
	fill_map(game);
	return (0);
}
