/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:44:26 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/15 12:26:05 by acarro-v         ###   ########.fr       */
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
