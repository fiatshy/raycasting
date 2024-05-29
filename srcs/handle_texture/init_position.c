/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_position.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:51:14 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/29 08:51:16 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_direction_nested(char c, t_info *ti)
{
	if (c == 'E')
	{
		ti->tv->dir[0] = 1;
		ti->tv->dir[1] = 0;
		ti->tv->plane[0] = 0;
		ti->tv->plane[1] = 0.66;
	}
	else if (c == 'W')
	{
		ti->tv->dir[0] = -1;
		ti->tv->dir[1] = 0;
		ti->tv->plane[0] = 0;
		ti->tv->plane[1] = -0.66;
	}
}

void	set_direction(char c, t_info *ti)
{
	if (c == 'N')
	{
		ti->tv->dir[0] = 0;
		ti->tv->dir[1] = -1;
		ti->tv->plane[0] = 0.66;
		ti->tv->plane[1] = 0;
		return ;
	}
	else if (c == 'S')
	{
		ti->tv->dir[0] = 0;
		ti->tv->dir[1] = 1;
		ti->tv->plane[0] = -0.66;
		ti->tv->plane[1] = 0;
		return ;
	}
	set_direction_nested(c, ti);
}

void	check_duplicate(int dup, t_info *ti)
{
	if (dup)
	{
		printf("map error: duplicate start position");
		free_all(ti);
		exit(0);
	}
}

void	find_position(t_info *ti)
{
	int	i;
	int	j;
	int	dup;

	i = 0;
	dup = -1;
	while (i < ti->arr_height)
	{
		j = 0;
		while (j < ti->arr_width)
		{
			if (ti->map[i][j] == 'N' || ti->map[i][j] == 'S' \
					|| ti->map[i][j] == 'E' || ti->map[i][j] == 'W')
			{
				set_direction(ti->map[i][j], ti);
				ti->map[i][j] = 0;
				ti->tv->arr_pos[0] = j + 0.5;
				ti->tv->arr_pos[1] = i + 0.5;
				dup++;
			}
			j++;
		}
		i++;
	}
	check_duplicate(dup, ti);
}
