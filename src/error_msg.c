/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:41:17 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/22 14:24:13 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_list(t_texture *texture)
{
	t_texture	*temp;

	while (texture)
	{
		temp = texture->next;
		if (texture->name)
			free(texture->name);
		if (texture->path)
			free(texture->path);
		free(texture);
		texture = temp;
	}
}

void	free_array(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->line_copy)
		free(data->line_copy);
	if (data->textures_line)
		free(data->textures_line);
	if (data->map_array)
		free_array(data->map_array);
	if (data->textures_split)
		free_array(data->textures_split);
	if (data->count)
		free(data->count);
	if (data->fd >= 0)
		close(data->fd);
	free(data);
}

void	free_game(t_game *game)
{
	if (game->mlx)
	{
		if (game->image)
			mlx_delete_image(game->mlx, game->image);
		if (game->tex_north)
			mlx_delete_texture(game->tex_north);;
		if (game->tex_south)
			mlx_delete_texture(game->tex_south);
		if (game->tex_west)
			mlx_delete_texture(game->tex_west);
		if (game->tex_east)
			mlx_delete_texture(game->tex_east);
		mlx_terminate(game->mlx);
	}
	if (game->texture)
		free_list(game->texture);
	if (game->data)
		free_data(game->data);
	free(game);
}

int	ft_error_msg(char *str, t_game *game)
{
	write(2, str, ft_strlen(str));
	if (game)
	{
		get_next_line(-1);// clean all the buffer (show leak in valgrind)
		free_game(game);
	}
	return (1);
}
