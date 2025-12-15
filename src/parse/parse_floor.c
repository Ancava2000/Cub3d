/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:20:09 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/15 14:06:26 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
