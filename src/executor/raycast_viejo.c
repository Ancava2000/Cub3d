/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:14:18 by azibechi          #+#    #+#             */
/*   Updated: 2026/01/11 16:53:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static uint32_t	get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	raycasting(t_game *game)
{
    int			x;
    t_ray		*ray;
    t_player	*p;
    uint32_t	ceil_color;
    uint32_t	floor_color;

    x = 0;
    ray = &game->raycasting;
    p = &game->player;
    ceil_color = get_rgba(game->ceiling.r, game->ceiling.g, game->ceiling.b, 255);
    floor_color = get_rgba(game->floor.r, game->floor.g, game->floor.b, 255);

    while (x < WIDTH)
    {
        // 1. Calculate ray position and direction
        ray->camera_x = 2 * x / (double)WIDTH - 1;
        ray->ray_dir.x = p->dir.x + p->plane.x * ray->camera_x;
        ray->ray_dir.y = p->dir.y + p->plane.y * ray->camera_x;

        // 2. Setup DDA
        int map_x = (int)p->pos.x;
        int map_y = (int)p->pos.y;

        ray->delta_dist.x = (ray->ray_dir.x == 0) ? 1e30 : fabs(1 / ray->ray_dir.x);
        ray->delta_dist.y = (ray->ray_dir.y == 0) ? 1e30 : fabs(1 / ray->ray_dir.y);

        if (ray->ray_dir.x < 0)
        {
            ray->step.x = -1;
            ray->side_dist.x = (p->pos.x - map_x) * ray->delta_dist.x;
        }
        else
        {
            ray->step.x = 1;
            ray->side_dist.x = (map_x + 1.0 - p->pos.x) * ray->delta_dist.x;
        }
        if (ray->ray_dir.y < 0)
        {
            ray->step.y = -1;
            ray->side_dist.y = (p->pos.y - map_y) * ray->delta_dist.y;
        }
        else
        {
            ray->step.y = 1;
            ray->side_dist.y = (map_y + 1.0 - p->pos.y) * ray->delta_dist.y;
        }

        // 3. Perform DDA
        int hit = 0;
        int side;
        while (hit == 0)
        {
            if (ray->side_dist.x < ray->side_dist.y)
            {
                ray->side_dist.x += ray->delta_dist.x;
                map_x += (int)ray->step.x;
                side = 0;
            }
            else
            {
                ray->side_dist.y += ray->delta_dist.y;
                map_y += (int)ray->step.y;
                side = 1;
            }

            // Bounds check
            if (map_y < 0 || map_y >= game->data->map_height)
            {
                hit = 1;
                break;
            }
            // Assuming map rows are null-terminated or we know width
            // Simple check to avoid segfault if map is not rectangular
            if (map_x < 0 || (size_t)map_x >= ft_strlen(game->data->map_array[map_y]))
            {
                hit = 1;
                break;
            }

            if (game->data->map_array[map_y][map_x] == '1')
                hit = 1;
        }

        // 4. Calculate distance
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
        else
            perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);

        if (perp_wall_dist < 1e-6) perp_wall_dist = 1e-6;

        // 5. Calculate line height and draw limits
        int line_height = (int)(HEIGHT / perp_wall_dist);
        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

        // 6. Select Texture
        mlx_texture_t *tex;
        if (side == 0) // Vertical hit (East/West)
        {
            if (ray->ray_dir.x > 0)
                tex = game->tex_west; // Hit left side of block -> West texture
            else
                tex = game->tex_east; // Hit right side of block -> East texture
        }
        else // Horizontal hit (North/South)
        {
            if (ray->ray_dir.y > 0)
                tex = game->tex_north; // Hit top side of block -> North texture
            else
                tex = game->tex_south; // Hit bottom side of block -> South texture
        }

        // 7. Calculate Texture X
        double wall_x;
        if (side == 0)
            wall_x = p->pos.y + perp_wall_dist * ray->ray_dir.y;
        else
            wall_x = p->pos.x + perp_wall_dist * ray->ray_dir.x;
        wall_x -= floor(wall_x);

        int tex_x = (int)(wall_x * (double)tex->width);
        if (side == 0 && ray->ray_dir.x > 0)
            tex_x = tex->width - tex_x - 1;
        if (side == 1 && ray->ray_dir.y < 0)
            tex_x = tex->width - tex_x - 1;

        // 8. Draw Vertical Strip
        // Draw Ceiling
        for (int y = 0; y < draw_start; y++)
            mlx_put_pixel(game->image, x, y, ceil_color);

        // Draw Wall
        double step = 1.0 * tex->height / line_height;
        double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;

        for (int y = draw_start; y < draw_end; y++)
        {
            int tex_y = (int)tex_pos % tex->height; // Use Modulo for safety
            tex_pos += step;
            // Ensure tex_y is positive
            if (tex_y < 0) tex_y = 0; 
            
            uint32_t color = get_tex_pixel(tex, tex_x, tex_y);
            mlx_put_pixel(game->image, x, y, color);
        }

        // Draw Floor
        for (int y = draw_end; y < HEIGHT; y++)
            mlx_put_pixel(game->image, x, y, floor_color);

        x++;
    }
}
// 8 y, x, draw_start, line_height, step, color
