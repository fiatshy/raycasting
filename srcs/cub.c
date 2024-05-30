/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:22:57 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/24 10:22:59 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_all(t_info *ti)
{
	int	i;

	free(ti->td->dir[0]);
	free(ti->td->dir[1]);
	free(ti->td->dir[2]);
	free(ti->td->dir[3]);
	free(ti->td->dir);
	free(ti->td->dir_path[0]);
	free(ti->td->dir_path[1]);
	free(ti->td->dir_path[2]);
	free(ti->td->dir_path[3]);
	free(ti->td->dir_path);
	free(ti->td->fc[0]);
	free(ti->td->fc[1]);
	free(ti->td->fc);
	free(ti->tc);
	free(ti->tx->tex->wall_ptr[0]);
	free(ti->tx->tex->wall_ptr[1]);
	free(ti->tx->tex->wall_ptr[2]);
	free(ti->tx->tex->wall_ptr[3]);
	free(ti->tx->tex->texture_ptr[0]);
	free(ti->tx->tex->texture_ptr[1]);
	free(ti->tx->tex->texture_ptr[2]);
	free(ti->tx->tex->texture_ptr[3]);
	free(ti->tx->tex->texture_ptr[4]);
	free(ti->tx->tex->texture_ptr[5]);
	free(ti->tx->tex->wall_ptr);
	free(ti->tx->tex);
	free(ti->tx);
	i = 0;
	while (i < ti->arr_height)
	{
		free(ti->map[i]);
		i++;
	}
	free(ti->map);
}

void	set_ti_time(t_info *ti)
{
	struct timeval	temp;

	gettimeofday(&temp, NULL);
	ti->old_time = temp.tv_sec * 1000000 + temp.tv_usec;
	ti->time = ti->old_time;
}

int	main(int ac, char **av)
{
	t_dir	td;
	t_info	ti;
	char	*mapfile = "./map.cub";

	(void) ac;
	(void) av;
	init_tdir(&td);
	ti.td = &td;
	set_ti_time(&ti);
	if (check_file(mapfile, &td, &ti) == -1)
		return (0);
	init_raycasting(&ti);
	free_all(&ti);
}
