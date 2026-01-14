/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:37:11 by azibechi          #+#    #+#             */
/*   Updated: 2026/01/12 16:20:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* void	ft_hooks(void *param)
{
	t_game		*game;
    t_player	*p;
    double		new_x;
    double		new_y;

    game = (t_game *)param;
    p = &game->player;

    // --- SALIR ---
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))  // con el anterior de close window daba segmentation fault. Así se libera todo y hace terminate al final
    {
		get_next_line(-1);
        free_game(game);
        exit(0);  // Salir del programa inmediatamente
    }
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
    {
        // Moverse en dirección negativa del plano (Izquierda)
        // Nota: A veces el vector plane apunta a la derecha, verifica el signo
        new_x = p->pos.x - p->plane.x * MOVE_SPEED;
        new_y = p->pos.y - p->plane.y * MOVE_SPEED;
        
        if (game->data->map_array[(int)p->pos.y][(int)new_x] != '1')
            p->pos.x = new_x;
        if (game->data->map_array[(int)new_y][(int)p->pos.x] != '1')
            p->pos.y = new_y;
    }

    // --- MOVIMIENTO LATERAL (D - Derecha) ---
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        // Moverse en dirección positiva del plano (Derecha)
        new_x = p->pos.x + p->plane.x * MOVE_SPEED;
        new_y = p->pos.y + p->plane.y * MOVE_SPEED;
        
        if (game->data->map_array[(int)p->pos.y][(int)new_x] != '1')
            p->pos.x = new_x;
        if (game->data->map_array[(int)new_y][(int)p->pos.x] != '1')
            p->pos.y = new_y;
    }
	
    // --- MOVIMIENTO (W) ---
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        new_x = p->pos.x + p->dir.x * MOVE_SPEED;
        new_y = p->pos.y + p->dir.y * MOVE_SPEED;
        // Colisión simple: Si la casilla destino no es pared, avanza
        if (game->data->map_array[(int)p->pos.y][(int)new_x] != '1')
            p->pos.x = new_x;
        if (game->data->map_array[(int)new_y][(int)p->pos.x] != '1')
            p->pos.y = new_y;
    }
    // --- MOVIMIENTO (S) ---
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        new_x = p->pos.x - p->dir.x * MOVE_SPEED;
        new_y = p->pos.y - p->dir.y * MOVE_SPEED;
        if (game->data->map_array[(int)p->pos.y][(int)new_x] != '1')
            p->pos.x = new_x;
        if (game->data->map_array[(int)new_y][(int)p->pos.x] != '1')
            p->pos.y = new_y;
    } 
    // ... Implementar A y D usando p->plane en vez de p->dir ...

    // --- ROTACIÓN (Flecha Derecha) ---
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
    {
        double old_dir_x = p->dir.x;
        double old_plane_x = p->plane.x;
        
        // Rotar vector dirección
        p->dir.x = p->dir.x * cos(ROT_SPEED) - p->dir.y * sin(ROT_SPEED);
        p->dir.y = old_dir_x * sin(ROT_SPEED) + p->dir.y * cos(ROT_SPEED);
        
        // Rotar vector plano (¡Es vital rotar ambos!)
        p->plane.x = p->plane.x * cos(ROT_SPEED) - p->plane.y * sin(ROT_SPEED);
        p->plane.y = old_plane_x * sin(ROT_SPEED) + p->plane.y * cos(ROT_SPEED);
    }
    // --- ROTACIÓN (Flecha Izquierda) ---
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
    {
        double old_dir_x = p->dir.x;
        double old_plane_x = p->plane.x;
        
        // Rotar sentido contrario (-ROT_SPEED)
        p->dir.x = p->dir.x * cos(-ROT_SPEED) - p->dir.y * sin(-ROT_SPEED);
        p->dir.y = old_dir_x * sin(-ROT_SPEED) + p->dir.y * cos(-ROT_SPEED);
        p->plane.x = p->plane.x * cos(-ROT_SPEED) - p->plane.y * sin(-ROT_SPEED);
        p->plane.y = old_plane_x * sin(-ROT_SPEED) + p->plane.y * cos(-ROT_SPEED);
    }
} */

static void	init_player(t_game *game)
{
    int x;
    int y;
    
	game->player.dir.x = 0;
	game->player.dir.y = 0;
	if (game->player.dir_name == 'N')
		game->player.dir.y = -1;
	if (game->player.dir_name == 'S')
		game->player.dir.y = 1;
	if (game->player.dir_name == 'E')
		game->player.dir.x = 1;
	if (game->player.dir_name == 'W')
		game->player.dir.x = -1;
	game->player.plane.x = -game->player.dir.y * 0.66;
	game->player.plane.y = game->player.dir.x * 0.66;
//	printf("\nDEBUG: Player Pos: x=%f, y=%f\n", game->player.pos.x, game->player.pos.y);
	x = (int)game->player.pos.x;
	y = (int)game->player.pos.y;
	game->data->map_array[y][x] = '0';
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_memset(game->image->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	raycasting(game);
}

void	load_game_textures(t_game *game)
{
    t_texture	*tmp;

    tmp = game->texture;
    while (tmp)
    {
        if (!ft_strncmp(tmp->name, "NO", 2))
            game->tex_north = mlx_load_png(tmp->path);
        else if (!ft_strncmp(tmp->name, "SO", 2))
            game->tex_south = mlx_load_png(tmp->path);
        else if (!ft_strncmp(tmp->name, "WE", 2))
            game->tex_west = mlx_load_png(tmp->path);
        else if (!ft_strncmp(tmp->name, "EA", 2))
            game->tex_east = mlx_load_png(tmp->path);
        tmp = tmp->next;
    }
    if (!game->tex_north || !game->tex_south || !game->tex_west || !game->tex_east)
    {
        ft_error_msg("Error: Could not load all textures (Check paths/PNG format)\n", game);
        exit(1);
    }
}

int	init_engine(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!game->mlx)
		return (ft_error_msg("mlx_init failed\n", game));
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return (ft_error_msg("mlx_new_image failed\n", game));
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
		return (ft_error_msg("mlx_image_to_window failed\n", game));
	init_player(game);
	load_game_textures(game);
	mlx_loop_hook(game->mlx, &ft_hooks, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_close_hook(game->mlx, &close_hook, game);
	mlx_loop(game->mlx);
	free_game(game);
	return (0);
}
