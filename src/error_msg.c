/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azibechi <azibechi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:41:17 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/18 20:34:27 by azibechi         ###   ########.fr       */
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
	free(data);
}

void	free_game(t_game *game)
{
	if (game->data)
		free_data(game->data);
	if (game->texture)
		free_list(game->texture);
	if (game->mlx)
	{
		if (game->image_no.ptr)
			mlx_delete_image(game->mlx, game->image_no.ptr);
		if (game->image_so.ptr)
			mlx_delete_image(game->mlx, game->image_so.ptr);
		if (game->image_ea.ptr)
			mlx_delete_image(game->mlx, game->image_ea.ptr);
		if (game->image_we.ptr)
			mlx_delete_image(game->mlx, game->image_we.ptr);
		if (game->image)
			mlx_delete_image(game->mlx, game->image);
		mlx_terminate(game->mlx);
	}
	free(game);
}

int	ft_error_msg(char *str, t_game *game)
{
	write(2, str, ft_strlen(str));
	if (game)
	{
		get_next_line(-1);  // clean all the buffer (show leak in valgrind)
		free_game(game);
	}
	return (1);
}
