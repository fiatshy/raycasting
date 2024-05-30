/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:37:28 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/27 13:37:29 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	key_up(t_info *ti)
{
	if (ti->map[(int)ti->tv->arr_pos[1]][(int) \
		(ti->tv->arr_pos[0] + ti->tv->dir[0] * ti->move_speed)] == 0)
		ti->tv->arr_pos[0] += ti->tv->dir[0] * ti->move_speed;
	if (ti->map[(int)(ti->tv->arr_pos[1] + \
		ti->tv->dir[1] * ti->move_speed)][(int)ti->tv->arr_pos[0]] == 0)
		ti->tv->arr_pos[1] += ti->tv->dir[1] * ti->move_speed;
}

void	key_down(t_info *ti)
{
	if (ti->map[(int)ti->tv->arr_pos[1]][(int) \
			(ti->tv->arr_pos[0] - ti->tv->dir[0] * ti->move_speed)] == 0)
		ti->tv->arr_pos[0] -= ti->tv->dir[0] * ti->move_speed;
	if (ti->map[(int)(ti->tv->arr_pos[1] - \
			ti->tv->dir[1] * ti->move_speed)][(int)ti->tv->arr_pos[0]] == 0)
		ti->tv->arr_pos[1] -= ti->tv->dir[1] * ti->move_speed;
}

void	key_left(t_info *ti)
{
	if (ti->map[(int)ti->tv->arr_pos[1]][(int) \
			(ti->tv->arr_pos[0] - ti->tv->plane[0] * ti->move_speed)] == 0)
		ti->tv->arr_pos[0] -= ti->tv->plane[0] * ti->move_speed;
	if (ti->map[(int)(ti->tv->arr_pos[1] - \
			ti->tv->plane[1] * ti->move_speed)][(int)ti->tv->arr_pos[0]] == 0)
		ti->tv->arr_pos[1] -= ti->tv->plane[1] * ti->move_speed;
}

void	key_right(t_info *ti)
{
	if (ti->map[(int)ti->tv->arr_pos[1]][(int) \
			(ti->tv->arr_pos[0] + ti->tv->plane[0] * ti->move_speed)] == 0)
		ti->tv->arr_pos[0] += ti->tv->plane[0] * ti->move_speed;
	if (ti->map[(int)(ti->tv->arr_pos[1] + \
		ti->tv->plane[1] * ti->move_speed)][(int)ti->tv->arr_pos[0]] == 0)
		ti->tv->arr_pos[1] += ti->tv->plane[1] * ti->move_speed;
}
