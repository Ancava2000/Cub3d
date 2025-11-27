/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:41:17 by acarro-v          #+#    #+#             */
/*   Updated: 2025/11/27 15:41:17 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
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
	if (data->texture_no)
		free(data->texture_no);
	if (data->texture_so)
		free(data->texture_so);
	if (data->texture_ea)
		free(data->texture_ea);
	if (data->texture_we)
		free(data->texture_we);
	if (data->f_color)
		free_array(data->f_color);
	if (data->c_color)
		free_array(data->c_color);
	free(data);
}

void	free_game(t_game *game)
{
	if (game->data)
		free_data(game->data);
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
