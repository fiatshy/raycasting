#include "cub.h"

int	control_keys(int key, void *data)
{
	t_info	*ti = data;
	if (key == LEFT)
	{
		double	old_dir_x = ti->tv->dir[0];
		double	rot_speed = 0.25;
		ti->tv->dir[0] = ti->tv->dir[0] * cos(-rot_speed) - ti->tv->dir[1] * sin(-rot_speed);
		ti->tv->dir[1] = old_dir_x * sin(-rot_speed) + ti->tv->dir[1] * cos(-rot_speed);
		double	old_plane_x = ti->tv->plane[0];
		ti->tv->plane[0] = ti->tv->plane[0] * cos(-rot_speed) - ti->tv->plane[1] * sin(-rot_speed);
		ti->tv->plane[1] = old_plane_x * sin(-rot_speed) + ti->tv->plane[1] * cos(-rot_speed);
	}
	else if (key == RIGHT)
	{

	}
	return (0);
}

void	init_config(t_info *ti)
{
	t_view	*tv;

	tv = malloc (sizeof (t_view));
	tv->arr_pos[0] = 3.5;
	tv->arr_pos[1] = 3.5;
	tv->dir[0] = 0;
	tv->dir[1] = -1;
	tv->plane[0] = 0.66;
	tv->plane[1] = 0;
	ti->tx->tex->sprite[0].x = 26.5;
	ti->tx->tex->sprite[0].y = 1.5;
	ti->tx->tex->sprite[0].texture = 10;
	ti->tx->tex->sprite[1].x = 28.5;
	ti->tx->tex->sprite[1].y = 1.5;
	ti->tx->tex->sprite[1].texture = 10;
	ti->tv = tv;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


void	fill_background(t_info *ti)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			put_pixel(ti->tx->img, j, i, ti->td->fc_value[0]);
			j++;
		}
		i++;
	}
}

void	fill_ceiling(t_info *ti)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_HEIGHT / 2)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			put_pixel(ti->tx->img, j, i, ti->td->fc_value[1]);
			j++;
		}
		i++;
	}
}

double	abs_double(double x)
{
	if (x < 0)
		return (-1 * x);
	return (x);
}

void	caclulate_distance_prepare(t_info *ti, t_distance *td, int x)
{
	td->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	td->ray_dir_x = ti->tv->dir[0] + ti->tv->plane[0] * td->camera_x;
	td->ray_dir_y = ti->tv->dir[1] + ti->tv->plane[1] * td->camera_x;

	td->map_x = (int)ti->tv->arr_pos[0];
	td->map_y = (int)ti->tv->arr_pos[1];

	td->delta_dist_x = (td->ray_dir_x == 0) ? 1e30 : abs_double(1 / td->ray_dir_x);
	td->delta_dist_y = (td->ray_dir_y == 0) ? 1e30 : abs_double(1 / td->ray_dir_y);
}

void	calculate_initial_distance(t_info *ti, t_distance *td)
{
	if (td->ray_dir_x < 0)
	{
		td->step_x = -1;
		td->side_dist_x = (ti->tv->arr_pos[0] - td->map_x) * td->delta_dist_x;
	}
	else
	{
		td->step_x = 1;
		td->side_dist_x = (td->map_x + 1.0 - ti->tv->arr_pos[0]) * td->delta_dist_x;
	}
	if (td->ray_dir_y < 0)
	{
		td->step_y = -1;
		td->side_dist_y = (ti->tv->arr_pos[1] - td->map_y) * td->delta_dist_y;
	}
	else
	{
		td->step_y = 1;
		td->side_dist_y = (td->map_y + 1.0 - ti->tv->arr_pos[1]) * td->delta_dist_y;
	}
}

void	calculate_distance_hit(t_info *ti, t_distance *td)
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
		if (ti->map[td->map_x][td->map_y] == 1)
		{
			td->hit = 1;
		}
	}
	if (td->side == 0)
		td->perp_wall_dist = (td->side_dist_x - td->delta_dist_x);
	else
		td->perp_wall_dist = (td->side_dist_y - td->delta_dist_y);
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
	tw->tex_pos = (tw->draw_start - tw->pitch - tw->h / 2 + tw->line_height / 2) * tw->step;
	y = tw->draw_start;
	while (y < tw->draw_end)
	{
		tw->tex_y = (int) tw->tex_pos & (TEXTURE_HEIGHT - 1);
		tw->tex_pos += tw->step;
		tw->color = ti->tx->tex->wall_addr[3][TEXTURE_HEIGHT * tw->tex_y + tw->tex_x];
		if (td->side == 1) 
			tw->color = (tw->color >> 1) & 8355711;
		put_pixel(ti->tx->img, x, y, tw->color);
		y++;
	}
}

void	calculate_distance(t_info *ti)
{
	int	x;
	t_distance	td;
	t_wall		tw;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		caclulate_distance_prepare(ti, &td, x);
		calculate_initial_distance(ti, &td);
		calculate_distance_hit(ti, &td);
		calculate_draw_value(ti, &tw, &td);
		draw_texture(ti, &tw, &td, x);
		x++;
	}
}

int	render_frame(void *data)
{
	t_info	*ti;
	
	ti = data;
	fill_background(ti);
	fill_ceiling(ti);
	calculate_distance(ti);
	mlx_put_image_to_window(ti->tx->mlx, ti->tx->mlx_win, ti->tx->img->img, 0, 0);
	return (0);
}

void	init_mlx_config(t_info *ti)
{
	mlx_hook(ti->tx->mlx_win, 2, 1L << 0, control_keys, (void *)ti);
	mlx_loop_hook(ti->tx->mlx, render_frame, (void*)ti);
	mlx_loop(ti->tx->mlx);
}