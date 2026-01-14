/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:11:18 by marvin            #+#    #+#             */
/*   Updated: 2026/01/12 15:11:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// ESTA FUNCION CREO Q ES ILEGAL, NO SE PUEDE USAR GNL
void close_hook(void *param)
{
    t_game *game = (t_game *)param;
    
    get_next_line(-1);
    free_game(game);
    exit(0);
}

static void    ft_hook_w_a(t_game game, t_player p)
{
    double		new_x;
    double		new_y;

    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        new_x = p->pos.x + p->dir.x * MOVE_SPEED;
        new_y = p->pos.y + p->dir.y * MOVE_SPEED;
        if (game->data->map_array[(int)p->pos.y][(int)new_x] != '1')
            p->pos.x = new_x;
        if (game->data->map_array[(int)new_y][(int)p->pos.x] != '1')
            p->pos.y = new_y;
    }
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
    {
        new_x = p->pos.x - p->plane.x * MOVE_SPEED;
        new_y = p->pos.y - p->plane.y * MOVE_SPEED;
        if (game->data->map_array[(int)p->pos.y][(int)new_x] != '1')
            p->pos.x = new_x;
        if (game->data->map_array[(int)new_y][(int)p->pos.x] != '1')
            p->pos.y = new_y;
    }
}

static void    ft_hook_s_d(t_game game, t_player p)
{
    double		new_x;
    double		new_y;

    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        new_x = p->pos.x - p->dir.x * MOVE_SPEED;
        new_y = p->pos.y - p->dir.y * MOVE_SPEED;
        if (game->data->map_array[(int)p->pos.y][(int)new_x] != '1')
            p->pos.x = new_x;
        if (game->data->map_array[(int)new_y][(int)p->pos.x] != '1')
            p->pos.y = new_y;
    }
        if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        new_x = p->pos.x + p->plane.x * MOVE_SPEED;
        new_y = p->pos.y + p->plane.y * MOVE_SPEED;
        if (game->data->map_array[(int)p->pos.y][(int)new_x] != '1')
            p->pos.x = new_x;
        if (game->data->map_array[(int)new_y][(int)p->pos.x] != '1')
            p->pos.y = new_y;
    }
}

static void    ft_hook_rotate(t_game game, t_player p)
{
    double old_dir_x;
    double old_plane_x;

    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
    {
        old_dir_x = p->dir.x;
        old_plane_x = p->plane.x;
        p->dir.x = p->dir.x * cos(ROT_SPEED) - p->dir.y * sin(ROT_SPEED);
        p->dir.y = old_dir_x * sin(ROT_SPEED) + p->dir.y * cos(ROT_SPEED);
        p->plane.x = p->plane.x * cos(ROT_SPEED) - p->plane.y * sin(ROT_SPEED);
        p->plane.y = old_plane_x * sin(ROT_SPEED) + p->plane.y * cos(ROT_SPEED);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
    {
        old_dir_x = p->dir.x;
        old_plane_x = p->plane.x;
        p->dir.x = p->dir.x * cos(-ROT_SPEED) - p->dir.y * sin(-ROT_SPEED);
        p->dir.y = old_dir_x * sin(-ROT_SPEED) + p->dir.y * cos(-ROT_SPEED);
        p->plane.x = p->plane.x * cos(-ROT_SPEED) - p->plane.y * sin(-ROT_SPEED);
        p->plane.y = old_plane_x * sin(-ROT_SPEED) + p->plane.y * cos(-ROT_SPEED);
    }
}

void	ft_hooks(void *param)
{
	t_game		*game;
    t_player	*p;


    game = (t_game *)param;
    p = &game->player;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
    {
		get_next_line(-1);
        free_game(game);
        exit(0);
    }
    ft_hook_w_a(game, p);
    ft_hook_s_d(game, p);
    ft_hook_rotate(game, p);
}
