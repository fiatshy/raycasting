/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:37:03 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/27 13:37:04 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fill_wall(t_info *ti, t_mini tm)
{
	int	i;
	int	j;

	i = tm.starty;
	while (i < tm.endy)
	{
		j = tm.startx;
		while (j < tm.endx)
		{
			put_pixel(ti->tx->img, i, j, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

void	fill_minimap_wall(t_info *ti)
{
	int		i;
	int		j;
	t_mini	tm;

	i = 0;
	while (i < ti->arr_width)
	{
		j = 0;
		while (j < ti->arr_width)
		{
			if (ti->map[j][i] == 1)
			{
				tm.starty = i * (SCREEN_WIDTH / 4 / ti->arr_height);
				tm.endy = (i + 1) * (SCREEN_WIDTH / 4 / ti->arr_height);
				tm.startx = j * (SCREEN_HEIGHT / 4 / ti->arr_width);
				tm.endx = (j + 1) * (SCREEN_HEIGHT / 4 / ti->arr_width);
				fill_wall(ti, tm);
			}
			j++;
		}
		i++;
	}
}

void	fill_minimap(t_info *ti)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_HEIGHT / 4)
	{
		j = 0;
		while (j < SCREEN_WIDTH / 4)
		{
			put_pixel(ti->tx->img, j, i, 0x00000000);
			j++;
		}
		i++;
	}
}
