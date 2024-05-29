/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:38:00 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/27 13:38:02 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	control_keys(int key, void *data)
{
	t_info	*ti;

	ti = data;
	if (key == LEFT_ARROW)
		key_left_arrows(ti);
	else if (key == RIGHT_ARROW)
		key_right_arrow(ti);
	else if (key == UP)
		key_up(ti);
	else if (key == DOWN)
		key_down(ti);
	else if (key == LEFT)
		key_left(ti);
	else if (key == RIGHT)
		key_right(ti);
	else if (key == SPACE)
		key_space(ti);
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
	ti->tx->tex->sprite[0].x = 20;
	ti->tx->tex->sprite[0].y = 3;
	ti->tx->tex->sprite[0].texture = 10;
	ti->tx->tex->sprite[1].x = 14.5;
	ti->tx->tex->sprite[1].y = 3;
	ti->tx->tex->sprite[1].texture = 10;
	ti->tx->tex->sprite[2].x = 22;
	ti->tx->tex->sprite[2].y = 3;
	ti->tx->tex->sprite[2].texture = 10;
	ti->tv = tv;
	find_position(ti);
}

int	close_window(void *data)
{
	t_info	*ti;

	ti = data;
	(void) ti;
	printf("close\n");
	free_all(ti);
	exit(0);
	return (0);
}

void	init_mlx_config(t_info *ti)
{
	mlx_hook(ti->tx->mlx_win, 17, 0, close_window, (void *) ti);
	mlx_hook(ti->tx->mlx_win, 2, 1L << 0, control_keys, (void *)ti);
	mlx_loop_hook(ti->tx->mlx, render_frame, (void *) ti);
	mlx_loop(ti->tx->mlx);
}
