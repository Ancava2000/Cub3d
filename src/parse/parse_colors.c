/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:52:24 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/10 17:54:02 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_range(char *color)
{
	int	num;
	int	i;

	i = 0;
	if (color[i] == 'F' || color[i] == 'C')
		i++;
	while (ft_isspace(color[i]))
		i++;
	while (color[i])
	{
		num = 0;
		while (ft_isspace(color[i]))
			i++;
		while (ft_isdigit(color[i]))
		{
			num = num * 10 + (color[i] - '0');
			i++;
		}
		if (num < 0 || num > 255)
		{
			ft_putstr_fd("Only a number between 0 and 255\n", 2);
			return (1);
		}
		while (ft_isspace(color[i]))
			i++;
		if (color[i] == ',')
			i++;
	}
	return (0);
}

int	check_number(char *color)
{
	int	i;

	i = 0;
	if (color[i] == 'F' || color[i] == 'C')
		i++;
	while (ft_isspace(color[i]))
		i++;
	while (color[i] && color[i] != '\n')
	{
		while (ft_isspace(color[i]))
			i++;
		if (color[i] == '\n' || color[i] == '\0')
			break ;
		if (color[i] == ',')
			i++;
		while (ft_isspace(color[i]))
			i++;
		if (!ft_isdigit(color[i]))
		{
			ft_putstr_fd("Only numbers and commas in color texture\n", 2);
			return (1);
		}
		while (ft_isdigit(color[i]))
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
	if (color[i] == 'F' || color[i] == 'C')
		i++;
	while (ft_isspace(color[i]))
		i++;
	while (color[i])
	{
		if (color[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		ft_putstr_fd("Incorrect number of commas, you need 2\n", 2);
		return (1);
	}
	return (0);
}

// In texture_split there are all the textures.
// Iterate to find colors.and all checks.
int	parse_colors(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->data->textures_split[i])
	{
		j = 0;
		if (game->data->textures_split[i][j] == 'F'
				|| game->data->textures_split[i][j] == 'C')
		{
			if (check_number(game->data->textures_split[i])
				|| count_commas(game->data->textures_split[i])
				|| check_range(game->data->textures_split[i]))
				return (ft_error_msg("Error with the color format\n", game));
		}
		i++;
	}
	return (0);
}
