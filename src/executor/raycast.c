/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   raycast.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: marvin <marvin@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/12/18 21:14:18 by azibechi		  #+#	#+#			 */
/*   Updated: 2026/01/11 16:53:25 by marvin		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* setup_ray: Initializes geometric values for the DDA algorithm.

1. camera_x: Converts pixel 'x' coord to horizontal camera space [-1, 1].
	-1 = left edge, 0 = center, 1 = right edge.
2. ray_dir: The direction vector of the ray. It is the sum of the
	player's direction vector and a portion of the camera plane vector.
3. delta_dist: Length of ray from one x or y-side to next x or y-side.
	Computed using Pythagoras (simplified to |1/ray_dir|). 
4. step: Grid step direction (-1 for left/up, +1 for right/down).
5. side_dist: Distance from start position to the FIRST x or y-side.
   Essentially aligns the ray start to the grid lines for the DDA loop. */

void	setup_ray(t_ray *ray, t_player *p, int x)
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

/*DDA: Digital Differential Analysis algorithm loop.

1. Iterates step-by-step through the map grid.
2. Always jumps to the nearest grid line (shortest side_dist).
3. Updates map position (map_x/y) and side hit (0=vertical, 1=horizontal).
4. Stops when a wall ('1') is hit or map boundaries are exceeded.*/

void	dda(t_ray *ray, t_game *game, int map_x, int map_y)
{
	ray->hit = 0;
	ray->side = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			map_x += (int)ray->step.x;
			ray->side = 0;
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
			break ;
		}
		if (game->data->map_array[map_y][map_x] == '1')
			ray->hit = 1;
	}
}



/* calc_distance: Computes wall distance and vertical drawing bounds.

1. perp_wall_dist: Calculates perpendicular distance to avoid fisheye effect.
	(Uses side_dist - delta_dist to backtrack one step from the wall hit).
2. line_height: Determines wall height on screen inversely proportional to 
	distance.
3. draw_start/end: Calculates top/bottom pixel coordinates for the wall strip,
   centered vertically on screen, clamped to screen boundaries (0 to HEIGHT). */

void	calc_distance(t_ray *ray)
{
	if (ray->side == 0)
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

/* If side = 0, the ray hits vertical (East or West). If ray_dir.x is > 0 
	Is West, else is East. horizontal hit with ray_dir.y > o is North */

void	select_texture(t_ray *ray, t_game *g, mlx_texture_t **tex, t_player *p)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir.x > 0)
			*tex = g->tex_west;
		else
			*tex = g->tex_east;
	}
	else
	{
		if (ray->ray_dir.y > 0)
			*tex = g->tex_north;
		else
			*tex = g->tex_south;
	}
	if (ray->side == 0)
		ray->wall_x = p->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		ray->wall_x = p->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)(*tex)->width);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		ray->tex_x = (*tex)->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		ray->tex_x = (*tex)->width - ray->tex_x - 1;
}

void	raycasting(t_game *game)
{
	int				x;
	t_ray			*ray;
	t_player		*p;
	mlx_texture_t	*tex;

	x = 0;
	ray = &game->raycasting;
	p = &game->player;
	while (x < WIDTH)
	{
		ray->x = x;
		setup_ray(ray, p, x);
		dda(ray, game, (int)p->pos.x, (int)p->pos.y);
		calc_distance(ray);
		select_texture(ray, game, &tex, p);
		ft_print_tex(ray, game, tex);
		x++;
	}
}

