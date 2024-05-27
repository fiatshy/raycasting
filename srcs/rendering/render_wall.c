/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:37:15 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/27 13:37:18 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	caclulate_distance_prepare(t_info *ti, t_distance *td, int x)
{
	td->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	td->ray_dir_x = ti->tv->dir[0] + ti->tv->plane[0] * td->camera_x;
	td->ray_dir_y = ti->tv->dir[1] + ti->tv->plane[1] * td->camera_x;
	td->map_x = (int)ti->tv->arr_pos[0];
	td->map_y = (int)ti->tv->arr_pos[1];
	if (td->ray_dir_x == 0)
		td->delta_dist_x = 1e30;
	else
		td->delta_dist_x = abs_double(1 / td->ray_dir_x);
	if (td->ray_dir_y == 0)
		td->delta_dist_y = 1e30;
	else
		td->delta_dist_y = abs_double(1 / td->ray_dir_y);
}

void	calculate_initial_distance(t_info *ti, t_distance *td)
{
	if (td->ray_dir_x < 0)
	{
		td->step_x = -1;
		td->side_dist_x = (ti->tv->arr_pos[0] - td->map_x) \
			* td->delta_dist_x;
	}
	else
	{
		td->step_x = 1;
		td->side_dist_x = (td->map_x + 1.0 - ti->tv->arr_pos[0]) \
			* td->delta_dist_x;
	}
	if (td->ray_dir_y < 0)
	{
		td->step_y = -1;
		td->side_dist_y = (ti->tv->arr_pos[1] - td->map_y) \
			* td->delta_dist_y;
	}
	else
	{
		td->step_y = 1;
		td->side_dist_y = (td->map_y + 1.0 - ti->tv->arr_pos[1]) \
			* td->delta_dist_y;
	}
}

void	calculate_distance_hit(t_info *ti, t_distance *td, int x)
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
		if (ti->map[td->map_y][td->map_x] == 1)
		{
			td->hit = 1;
		}
	}
	if (td->side == 0)
		td->perp_wall_dist = (td->side_dist_x - td->delta_dist_x);
	else
		td->perp_wall_dist = (td->side_dist_y - td->delta_dist_y);
	ti->tx->tex->dist_buffer[x] = td->perp_wall_dist;
}

void	calculate_draw_value(t_info *ti, t_wall *tw, t_distance *td)
{
	tw->h = SCREEN_HEIGHT;
	tw->line_height = (int)(tw->h / td->perp_wall_dist);
	tw->pitch = 0;
	tw->draw_start = ((-1 * tw->line_height)) / 2 + tw->h / 2;
	if (tw->draw_start < 0)
		tw->draw_start = 0;
	tw->draw_end = tw->line_height / 2 + tw->h / 2;
	if (tw->draw_end >= tw->h)
		tw->draw_end = tw->h - 1;
	if (td->side == 0)
		tw->wall_x = ti->tv->arr_pos[1] + td->perp_wall_dist * td->ray_dir_y;
	else
		tw->wall_x = ti->tv->arr_pos[0] + td->perp_wall_dist * td->ray_dir_x;
	tw->wall_x -= floor(tw->wall_x);
}

void	draw_texture(t_info *ti, t_wall *tw, t_distance *td, int x)
{
	int	y;

	tw->tex_x = (int)(tw->wall_x * (double)TEXTURE_WIDTH);
	if (td->side == 0 && td->ray_dir_x > 0)
		tw->tex_x = TEXTURE_WIDTH - tw->tex_x - 1;
	if (td->side == 1 && td->ray_dir_y < 0)
		tw->tex_x = TEXTURE_WIDTH - tw->tex_x - 1;
	tw->step = 1.0 * TEXTURE_HEIGHT / tw->line_height;
	tw->tex_pos = (tw->draw_start - tw->pitch - tw->h / 2 \
		+ tw->line_height / 2) * tw->step;
	y = tw->draw_start;
	while (y < tw->draw_end)
	{
		tw->tex_y = (int) tw->tex_pos & (TEXTURE_HEIGHT - 1);
		tw->tex_pos += tw->step;
		tw->color = ti->tx->tex->wall_addr[3][TEXTURE_HEIGHT \
			* tw->tex_y + tw->tex_x];
		if (td->side == 1)
			tw->color = (tw->color >> 1) & 8355711;
		put_pixel(ti->tx->img, x, y, tw->color);
		y++;
	}
}
