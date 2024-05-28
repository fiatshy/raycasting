#include "cub.h"

void	handle_door(t_info *ti, t_distance *td)
{
	if (ti->map[td->map_y][td->map_x] >= 3)
	{
		ti->tx->tex->count++;
		if (ti->tx->tex->count == 10000 || ti->tx->tex->count == 20000 \
			|| ti->tx->tex->count == 30000)
			ti->map[td->map_y][td->map_x] += 1;
	}
	if (ti->map[td->map_y][td->map_x] == 5)
	{
		ti->map[td->map_y][td->map_x] = 0;
		ti->tx->tex->count = 0;
	}
}

void	calculate_distance_hit_test(t_info *ti, t_distance *td, int x)
{
	td->hit = 0;
	while (td->hit == 0)
	{
		if (td->side_dist_x < td->side_dist_y)
		{
			td->side_dist_x += td->delta_dist_x;
			td->map_x += td->step_x;
			td->side = 0;
		}
		else
		{
			td->side_dist_y += td->delta_dist_y;
			td->map_y += td->step_y;
			td->side = 1;
		}
		if (ti->map[td->map_y][td->map_x] >= 1)
			td->hit = 1;
		handle_door(ti, td);
	}
	if (td->side == 0)
		td->perp_wall_dist = (td->side_dist_x - td->delta_dist_x);
	else
		td->perp_wall_dist = (td->side_dist_y - td->delta_dist_y);
	ti->tx->tex->dist_buffer[x] = td->perp_wall_dist;
}