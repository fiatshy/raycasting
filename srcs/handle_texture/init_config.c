#include "cub.h"

int	control_keys(int key, void *data)
{
	t_info	*ti;
	double	old_dir_x;
	double	rot_speed;
	double	old_plane_x;

	ti = data;
	if (key == LEFT)
	{
		old_dir_x = ti->tv->dir[0];
		rot_speed = 0.25;
		ti->tv->dir[0] = ti->tv->dir[0] * cos(-rot_speed) \
			- ti->tv->dir[1] * sin(-rot_speed);
		ti->tv->dir[1] = old_dir_x * sin(-rot_speed) \
			+ ti->tv->dir[1] * cos(-rot_speed);
		old_plane_x = ti->tv->plane[0];
		ti->tv->plane[0] = ti->tv->plane[0] * cos(-rot_speed) \
			- ti->tv->plane[1] * sin(-rot_speed);
		ti->tv->plane[1] = old_plane_x * sin(-rot_speed) \
			+ ti->tv->plane[1] * cos(-rot_speed);
	}
	return (0);
}

void	init_config(t_info *ti)
{
	t_view	*tv;

	tv = malloc (sizeof (t_view));
	tv->arr_pos[0] = 2.5;
	tv->arr_pos[1] = 3.5;
	tv->dir[0] = 0;
	tv->dir[1] = -1;
	tv->plane[0] = 0.66;
	tv->plane[1] = 0;
	ti->tx->tex->sprite[0].x = 3.5;
	ti->tx->tex->sprite[0].y = 2.5;
	ti->tx->tex->sprite[0].texture = 10;
	ti->tx->tex->sprite[1].x = 2.5;
	ti->tx->tex->sprite[1].y = 2.5;
	ti->tx->tex->sprite[1].texture = 10;
	ti->tv = tv;
}

void	init_mlx_config(t_info *ti)
{
	mlx_hook(ti->tx->mlx_win, 2, 1L << 0, control_keys, (void *)ti);
	mlx_loop_hook(ti->tx->mlx, render_frame, (void *) ti);
	mlx_loop(ti->tx->mlx);
}
