/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:41:17 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/08 11:45:23 by acarro-v         ###   ########.fr       */
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
	if (game->image_no.ptr)
		mlx_destroy_image(game->mlx, game->image_no.ptr);
	if (game->image_so.ptr)
		mlx_destroy_image(game->mlx, game->image_so.ptr);
	if (game->image_ea.ptr)
		mlx_destroy_image(game->mlx, game->image_ea.ptr);
	if (game->image_we.ptr)
		mlx_destroy_image(game->mlx, game->image_we.ptr);
	if (game->image)
		mlx_destroy_image(game->mlx, game->image);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game);
}

int	ft_error_msg(char *str, t_game *game)
{
	write(2, str, ft_strlen(str));
	if (game)
		free_game(game);
	return (1);
}
