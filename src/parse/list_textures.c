/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:14:40 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/08 15:06:43 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	add_node(t_game *game, t_texture *new)
{
	t_texture	*current;

	if (!game->texture)
	{
		game->texture = new;
		return ;
	}
	current = game->texture;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	get_path(char *line, int j)
{
	while (ft_isspace(line[j]))
		j++;
	return (j);
}

t_texture	*create_texture(t_game *game, int i)
{
	int			j;
	char		**textures;
	t_texture	*new_texture;

	j = 0;
	textures = game->data->textures_split;
	new_texture = ft_calloc(1, sizeof(t_texture));
	if (!new_texture)
		ft_error_msg("Failed to allocate count\n", game);
	while (ft_isspace(textures[i][j]))
		j++;
	new_texture->name = ft_substr(textures[i], j, 2);
	if (!new_texture->name)
		ft_error_msg("Failed to allocate texture\n", game);
	new_texture->path = ft_substr(textures[i], get_path(textures[i], j + 2),
			ft_strlen(textures[i]) - get_path(textures[i], j + 2));
	if (!new_texture->path)
		ft_error_msg("Failed to allocate texture\n", game);
	new_texture->next = NULL;
	return (new_texture);
}

int	list_textures(t_game *game)
{
	int			i;
	t_texture	*temp;

	i = 0;
	while (game->data->textures_split[i])
	{
		if (!ft_strncmp(game->data->textures_split[i], "NO", 2)
			|| !ft_strncmp(game->data->textures_split[i], "SO", 2)
			|| !ft_strncmp(game->data->textures_split[i], "WE", 2)
			|| !ft_strncmp(game->data->textures_split[i], "EA", 2))
		{
			temp = create_texture(game, i);
			if (!temp)
				return (1);
			add_node(game, temp);
		}
		i++;
	}
	return (0);
}
