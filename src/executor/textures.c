/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:49:34 by marvin            #+#    #+#             */
/*   Updated: 2026/01/12 15:49:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void load_textures(t_game *game)
{
    game->tex_north = mlx_load_png("src/textures/boca.png");
    game->tex_south = mlx_load_png("src/textures/ravioles.png");
    game->tex_east = mlx_load_png("src/textures/boca.png");
    game->tex_west = mlx_load_png("src/textures/boca.png");

    if (!game->tex_north || !game->tex_south || !game->tex_east || !game->tex_west)
    {
        puts(mlx_strerror(mlx_errno)); //CREO QUE PUTS NO SE PUEDE USAR
        ft_error_msg("Failed to load textures\n", game);
        exit(1);
    }
}

// Función auxiliar para obtener el pixel de una textura
uint32_t get_tex_pixel(mlx_texture_t *tex, int x, int y)
{
    int index;

    if (x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
        return (0);
    index = (y * tex->width + x) * 4; 
    uint8_t r = tex->pixels[index];
    uint8_t g = tex->pixels[index + 1];
    uint8_t b = tex->pixels[index + 2];
    uint8_t a = tex->pixels[index + 3];
    return ((r << 24) | (g << 16) | (b << 8) | a);
}

//INTENTE PRESCINDIR DE GET_TEX_PIXEL ACA
void    ft_print_tex(t_ray ray, t_game game, t_player p, mlx_texture_t tex)
{
    double      step;
    double      tex_pos;
    int         y;
    uint32_t    color;
    int         i;

    y = 0;
    while(y < ray->draw_start)
        mlx_put_pixel(game->image, x, y++, game->ceiling);
    double step = 1.0 * tex->height / ray->line_height;
    double tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
    y = ray->draw_start;
    while(y < ray->draw_end)
    {
        ray->tex_y = (int)tex_pos % tex->height;
        tex_pos += step;
        if (ray->tex_y < 0)
            ray->tex_y = 0; 
        i = (y * tex->width + x) * 4; 
        color = (tex->pixels[i] << 24) | (tex->pixels[i + 1] << 16)
            | (tex->pixels[i + 2] << 8) | tex->pixels[i + 3];
        mlx_put_pixel(game->image, x, y++, color);
    }
    while(y < HEIGHT)
        mlx_put_pixel(game->image, x, y++, game->floor);
}
