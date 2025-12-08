/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 08:37:24 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/08 14:52:43 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	create_color(t_game *game, int i)
{
	int			j;
	char		**textures;
	t_color		*color;
	char		**rgb;

	j = 0;
	textures = game->data->textures_split;
	while (ft_isspace(textures[i][j]))
		j++;
	if (textures[i][j] == 'C')
		color = &game->ceiling;
	else if (textures[i][j] == 'F')
		color = &game->floor;
	j++;
	while (ft_isspace(textures[i][j]))
		j++;
	rgb = ft_split(&textures[i][j], ',');
	if (!rgb)
		return (ft_error_msg("Error with color split\n", game));
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free_array(rgb);
	return (0);
}

int	list_colors(t_game *game)
{
	int	i;

	i = 0;
	while (game->data->textures_split[i])
	{
		if (!ft_strncmp(game->data->textures_split[i], "C", 1)
			|| !ft_strncmp(game->data->textures_split[i], "F", 1))
		{
			if (create_color(game, i))
				return (ft_error_msg("Error with colors\n", game));
		}
		i++;
	}
	return (0);
}
