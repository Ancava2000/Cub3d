/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azibechi <azibechi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:18:41 by azibechi          #+#    #+#             */
/*   Updated: 2026/01/14 18:18:41 by azibechi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_textures(t_game *game)
{
	game->tex_north = mlx_load_png("src/textures/boca.png");
	game->tex_south = mlx_load_png("src/textures/ravioles.png");
	game->tex_east = mlx_load_png("src/textures/boca.png");
	game->tex_west = mlx_load_png("src/textures/boca.png");

	if (!game->tex_north || !game->tex_south
		|| !game->tex_east || !game->tex_west)
	{
		ft_putendl_fd(mlx_strerror(mlx_errno), 2);
		//puts(mlx_strerror(mlx_errno)); //CREO QUE PUTS NO SE PUEDE USAR
		ft_error_msg("Failed to load textures\n", game);
		exit(1);
	}
}

int	ft_print_tex(t_ray *ray, t_game *game, mlx_texture_t *tex, int y)
{
	int			i;

	if (ray->line_height == 0)
		ray->tex_step = 0;
	else
		ray->tex_step = 1.0 * tex->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->tex_step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos % tex->height;
		ray->tex_pos += ray->tex_step;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		i = (ray->tex_y * tex->width + ray->tex_x) * 4;
		if (i >= 0 && i < (int)(tex->width * tex->height * 4))
		{
			ray->color = (tex->pixels[i] << 24) | (tex->pixels[i + 1] << 16)
				| (tex->pixels[i + 2] << 8) | tex->pixels[i + 3];
			mlx_put_pixel(game->image, ray->x, y, ray->color);
		}
		y++;
	}
	return (y);
}


