/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:44:26 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/18 13:28:24 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->data->map_array[i])
	{
		j = 0;
		while (game->data->map_array[i][j])
		{
			if (!ft_strchr(" 01NSEW\n", game->data->map_array[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_player(t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (game->data->map_array[i])
	{
		j = 0;
		while (game->data->map_array[i][j])
		{
			if (ft_strchr("NSEW", game->data->map_array[i][j]))
			{
				count++;
				game->player.pos_x = j + 0.5;
				game->player.pos_y = i + 0.5;
				game->player.dir = game->data->map_array[i][j];
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (1);
	return (0);
}

int	check_open(t_game *game, int x, int y)
{
	char	square;

	if (x < 0 || y < 0)
		return (1);
	square = game->data->map_array[x][y];
	if (square == ' ')
		return (1);
	return (0);
}

int	parse_open(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->data->map_array[x])
	{
		y = 0;
		while (game->data->map_array[x][y])
		{
			if (game->data->map_array[x][y] == '0'
				|| game->data->map_array[x][y] == 'N'
				|| game->data->map_array[x][y] == 'S'
				|| game->data->map_array[x][y] == 'W'
				|| game->data->map_array[x][y] == 'E')
			{
				if (check_open(game, (x + 1), y) || check_open(game, (x - 1), y)
					|| check_open(game, x, (y + 1))
					|| check_open(game, x, (y - 1)))
					return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}
