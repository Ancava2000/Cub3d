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

void    setup_ray(t_ray *ray, t_player *p)
{
    ray->camera_x = 2 * x / (double)WIDTH - 1;
    ray->ray_dir.x = p->dir.x + p->plane.x * ray->camera_x;
    ray->ray_dir.y = p->dir.y + p->plane.y * ray->camera_x;
    if (ray->ray_dir.x == 0)
        ray->delta_dist.x = 1e30;
    else
        ray->delta_dist.x = fabs(1.0 / ray->ray_dir.x);
    if (ray->ray_dir.y == 0)
        ray->delta_dist.y = 1e30;
    else
        ray->delta_dist.y = fabs(1.0 / ray->ray_dir.y);
    ray->step.x = 1;
    ray->side_dist.x = ((int)p->pos.x + 1.0 - p->pos.x) * ray->delta_dist.x;
    if (ray->ray_dir.x < 0)
    {
        ray->step.x = -1;
        ray->side_dist.x = (p->pos.x - (int)p->pos.x) * ray->delta_dist.x;
    }
    ray->step.y = 1;
    ray->side_dist.y = ((int)p->pos.y + 1.0 - p->pos.y) * ray->delta_dist.y;
    if (ray->ray_dir.y < 0)
    {
        ray->step.y = -1;
        ray->side_dist.y = (p->pos.y - (int)p->pos.y) * ray->delta_dist.y;
    }
}

void    dda(t_ray ray, int map_x, int map_y)
{
    ray->hit = 0;
    ray->side = 0;
    while (ray->hit == 0)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            map_x += (int)ray->step.x;
        }
        else
        {
            ray->side_dist.y += ray->delta_dist.y;
            map_y += (int)ray->step.y;
            ray->side = 1;
        }
        if (map_y < 0 || map_y >= game->data->map_height || map_x < 0
             || (size_t)map_x >= ft_strlen(game->data->map_array[map_y]))
        {
            ray->hit = 1;
            break;
        }
        if (game->data->map_array[map_y][map_x] == '1')
            ray->hit = 1;
    }
}

void    calc_distance(t_ray *ray)
{
    if (side == 0)
        ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
    else
        ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
    if (ray->perp_wall_dist < 1e-6) 
        ray->perp_wall_dist = 1e-6;
    ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
    ray->draw_start = -(ray->line_height) / 2 + HEIGHT / 2;
    if (ray->draw_start < 0) 
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_end >= HEIGHT) 
        ray->draw_end = HEIGHT - 1;
}

void   select_texture(t_ray ray, t_game game, mlx_texture_t, **tex, t_player *p)
{
    if (ray->side == 0) // Vertical hit (East/West)
    {
        if (ray->ray_dir.x > 0)
            *tex = game->tex_west; // Hit left side of block -> West texture
        else
            *tex = game->tex_east; // Hit right side of block -> East texture
    }
    else // Horizontal hit (North/South)
    {
        if (ray->ray_dir.y > 0)
            *tex = game->tex_north; // Hit top side of block -> North texture
        else
            *tex = game->tex_south; // Hit bottom side of block -> South texture
    }
    if (ray->side == 0)
        ray->wall_x = p->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
    else
        ray->wall_x = p->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
    ray->wall_x -= floor(ray->wall_x);
    ray->tex_x = (int)(ray->wall_x * (double)tex->width);
    if (ray->side == 0 && ray->ray_dir.x > 0)
        ray->tex_x = tex->width - ray->tex_x - 1;
    if (ray->side == 1 && ray->ray_dir.y < 0)
        ray->tex_x = tex->width - ray->tex_x - 1;
}

void	raycasting(t_game *game)
{
    int			    x;
    t_ray		    *ray;
    t_player	    *p;
    mlx_texture_t   *tex;

    x = 0;
    ray = &game->raycasting;
    p = &game->player;
    while (x < WIDTH)
    {
        setup_ray(ray, p);
        dda(ray, (int)p->pos.x, (int)p->pos.y);
        calc_distance(ray);
        select_texture(ray, game, &tex, p);
        ft_print_tex(ray, game, p, tex);
        x++;
    }
}

