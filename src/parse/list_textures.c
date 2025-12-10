/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:14:40 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/10 17:29:45 by acarro-v         ###   ########.fr       */
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

// returns the node with the name and path of the texture
t_texture	*create_texture(t_game *game, int i)
{
	int			j;
	int			end;
	char		**textures;
	t_texture	*new_texture;

	textures = game->data->textures_split;
	new_texture = ft_calloc(1, sizeof(t_texture));
	if (!new_texture)
		ft_error_msg("Failed to allocate count\n", game);
	new_texture->name = ft_substr(textures[i], 0, 2);
	if (!new_texture->name)
		ft_error_msg("Failed to allocate texture\n", game);
	j = 2;
	while (ft_isspace(textures[i][j]))
		j++;
	end = ft_strlen(textures[i]) - 1;
	while (end > j && ft_isspace(textures[i][end]))
		end--;
	new_texture->path = ft_substr(textures[i], j, end - j + 1);
	if (!new_texture->path)
		ft_error_msg("Failed to allocate texture\n", game);
	new_texture->next = NULL;
	return (new_texture);
}

// only create the texture node when it starts with NO, SO, WE,or EA
// then add the node to the linked list
int	list_textures(t_game *game)
{
	int			i;
	t_texture	*new_node;

	i = 0;
	while (game->data->textures_split[i])
	{
		if (!ft_strncmp(game->data->textures_split[i], "NO", 2)
			|| !ft_strncmp(game->data->textures_split[i], "SO", 2)
			|| !ft_strncmp(game->data->textures_split[i], "WE", 2)
			|| !ft_strncmp(game->data->textures_split[i], "EA", 2))
		{
			new_node = create_texture(game, i);
			if (!new_node)
				return (1);
			add_node(game, new_node);
		}
		i++;
	}
	return (0);
}
