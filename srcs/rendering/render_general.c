/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_general.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:27:43 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/27 13:27:44 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	calculate_fps(t_info *ti)
{
	struct timeval	temp;
	double			fps;

	gettimeofday(&temp, NULL);
	ti->old_time = ti->time;
	ti->time = temp.tv_sec * 1000000 + temp.tv_usec;
	fps = 1000 / ((ti->time - ti->old_time) / 1000);
	ti->move_speed = 10 / fps * 7.5;
	ti->rot_speed = 10 / fps * 7.5;
}

int	render_frame(void *data)
{
	t_info	*ti;

	ti = data;
	fill_background(ti);
	fill_ceiling(ti);
	calculate_distance(ti);
	fill_minimap(ti);
	fill_minimap_wall(ti);
	put_pixel(ti->tx->img, ti->tv->arr_pos[0] \
		* (SCREEN_WIDTH / 4 / ti->arr_width), \
			ti->tv->arr_pos[1] * \
			(SCREEN_HEIGHT / 4 / ti->arr_height), 0x00FF0000);
	mlx_put_image_to_window(ti->tx->mlx, ti->tx->mlx_win, \
		ti->tx->img->img, 0, 0);
	calculate_fps(ti);
	return (0);
}
