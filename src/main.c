/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarro-v <acarro-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 05:38:07 by acarro-v          #+#    #+#             */
/*   Updated: 2025/11/27 14:53:37 by acarro-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	
	game = ft_calloc(1, sizeof (t_game));
	if (!game)
		ft_error_msg("Error allocating memory for game", game);
	game->data = ft_calloc(1, sizeof(t_data));
	if (!game->data)
		ft_error_msg("Error allocating memory for data", game);
	if (check_args(ac, av))
		return (-1);
	if (parse(ac, av))
		return (-1);
	if (init_game(game))
		return (-1);
	return (0);
}