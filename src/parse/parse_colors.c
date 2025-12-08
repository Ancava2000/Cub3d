/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:52:24 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/08 13:45:41 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_range(char *color)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (ft_isspace(color[i]))
		i++;
	if (color[i] == 'F' || color[i] == 'C')
		i++;
	while (ft_isspace(color[i]))
		i++;
	while (ft_isdigit(color[i]))
	{
		num = num * 10 + (color[i] - '0');
		i++;
	}
	if (num < 0 || num > 255)
		return (1);
	return (0);
}

int	check_number(char *color)
{
	int	i;

	i = 0;
	while (ft_isspace(color[i]))
		i++;
	if (color[i] == 'F' || color[i] == 'C')
		i++;
	while (ft_isspace(color[i]))
		i++;
	while (color[i])
	{
		if (color[i] == ',')
			i++;
		if (!ft_isdigit(color[i]))
			return (1);
		i++;
	}
	return (0);
}

int	count_commas(char *color)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (ft_isspace(color[i]))
		i++;
	while (color[i])
	{
		if (color[i] == ',' && ft_isdigit(color[i +1])
			&& ft_isdigit(color[i - 1]))
			count++;
		i++;
	}
	if (count != 2)
		return (1);
	return (0);
}

int	parse_colors(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->data->textures_split[i])
	{
		j = 0;
		while (ft_isspace(game->data->textures_split[i][j]))
			j++;
		if (game->data->textures_split[i][j] == 'F'
				|| game->data->textures_split[i][j] == 'C')
		{
			if (count_commas(game->data->textures_split[i])
				|| check_number(game->data->textures_split[i])
				|| check_range(game->data->textures_split[i]))
				return (ft_error_msg("Error with the colors\n", game));
		}
		i++;
	}
	return (0);
}
