/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 08:37:24 by acarro-v          #+#    #+#             */
/*   Updated: 2026/01/12 15:35:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* aca cambié la forma en la que se almacena el color, porque para hacerlo operativo
	habia que hacerle una operación, entonces pense que no tenia mucho sentido almacenar
	R G y B. */

int	create_color(t_game *game, int i)
{
	int			j;
	char		**textures;
	uint32_t	*color;
	char		**rgb;

	j = 0;
	textures = game->data->textures_split;
	if (textures[i][j] == 'C')
		color = &game->ceiling_color;
	else if (textures[i][j] == 'F')
		color = &game->floor_color;
	j++;
	while (ft_isspace(textures[i][j]))
		j++;
	rgb = ft_split(&textures[i][j], ',');
	if (!rgb)
		return (ft_error_msg("Error with color split\n", game));
	color = (ft_atoi(rgb[0]) << 24 | ft_atoi(rgb[1]) << 16 | ft_atoi(rgb[2]) << 8 | 255);
/* 	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]); */
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
