/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:37:26 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/27 13:37:27 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	key_left_arrows(t_info *ti)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = ti->tv->dir[0];
	ti->tv->dir[0] = ti->tv->dir[0] * cos(-ti->rot_speed) \
		- ti->tv->dir[1] * sin(-ti->rot_speed);
	ti->tv->dir[1] = old_dir_x * sin(-ti->rot_speed) \
		+ ti->tv->dir[1] * cos(-ti->rot_speed);
	old_plane_x = ti->tv->plane[0];
	ti->tv->plane[0] = ti->tv->plane[0] * cos(-ti->rot_speed) \
		- ti->tv->plane[1] * sin(-ti->rot_speed);
	ti->tv->plane[1] = old_plane_x * sin(-ti->rot_speed) \
		+ ti->tv->plane[1] * cos(-ti->rot_speed);
}

void	key_right_arrow(t_info *ti)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = ti->tv->dir[0];
	ti->tv->dir[0] = ti->tv->dir[0] * cos(ti->rot_speed) \
		- ti->tv->dir[1] * sin(ti->rot_speed);
	ti->tv->dir[1] = old_dir_x * sin(ti->rot_speed) \
		+ ti->tv->dir[1] * cos(ti->rot_speed);
	old_plane_x = ti->tv->plane[0];
	ti->tv->plane[0] = ti->tv->plane[0] * cos(ti->rot_speed) \
		- ti->tv->plane[1] * sin(ti->rot_speed);
	ti->tv->plane[1] = old_plane_x * sin(ti->rot_speed) \
		+ ti->tv->plane[1] * cos(ti->rot_speed);
}
