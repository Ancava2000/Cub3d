/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azibechi <azibechi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:38:07 by acarro-v          #+#    #+#             */
/*   Updated: 2025/12/11 17:50:50 by azibechi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_textures_raw(t_game *game)
{
    printf("\n=== TEXTURES_LINE (raw string) ===\n");
    printf("'%s'\n", game->data->textures_line);
}

void	print_textures_split(t_game *game)
{
    int i = 0;
    
    printf("\n=== TEXTURES_SPLIT (array after split) ===\n");
    while (game->data->textures_split[i])
    {
        printf("[%d]: '%s'\n", i, game->data->textures_split[i]);
        i++;
    }
}

void	print_texture_list(t_game *game)
{
    t_texture *current = game->texture;
    int i = 0;
    
    printf("\n=== TEXTURE LINKED LIST ===\n");
    while (current)
    {
        printf("Node %d:\n", i);
        printf("  Name: '%s'\n", current->name);
        printf("  Path: '%s'\n", current->path);
        current = current->next;
        i++;
    }
}

void	print_colors(t_game *game)
{
    printf("\n=== COLORS ===\n");
    printf("Ceiling: R=%d G=%d B=%d\n", 
        game->ceiling.r, game->ceiling.g, game->ceiling.b);
    printf("Floor:   R=%d G=%d B=%d\n", 
        game->floor.r, game->floor.g, game->floor.b);
}

// Init all the parse data
int	init_parse(t_game *game)
{
	game->data->fd = -1;
	game->data->line = NULL;
	game->data->map_array = NULL;
	game->data->textures_line = ft_strdup("");
	game->data->textures_split = NULL;
	game->data->count = ft_calloc(1, sizeof(t_count));
	if (!game->data->count)
		return (ft_error_msg("Failed to allocate count\n", game));
	game->texture = NULL;
	return (0);
}

int	check_args(int ac, char **av, t_game *game)
{
	char	*extension;

	if (ac != 2)
		return (ft_error_msg("Only two arguments: ./cub3d + *.cub\n", game));
	extension = ft_strrchr(av[1], '.');
	if (!extension || ft_strncmp(extension, ".cub", 5) != 0)
		return (ft_error_msg("Not the correct extension. It must be .cub\n",
				game));
	return (0);
}

//Allocate memory and call all functions
int	main(int ac, char **av)
{
	t_game	*game;

	game = ft_calloc(1, sizeof (t_game));
	if (!game)
		return (ft_error_msg("Error allocating memory for game\n", game));
	game->data = ft_calloc(1, sizeof(t_data));
	if (!game->data)
		return (ft_error_msg("Error allocating memory for data\n", game));
	if (init_parse(game))
		return (-1);
	if (check_args(ac, av, game))
		return (-1);
	if (parse(av, game))
		return (-1);   
	print_textures_raw(game);
    print_textures_split(game);
    print_texture_list(game);
    print_colors(game);
	init_engine(game);
	free_game(game);
	return (0);
}
