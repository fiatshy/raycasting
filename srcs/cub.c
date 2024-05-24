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

int	main(int ac, char **av)
{
	t_dir	td;
	t_info	ti;
	char	*mapfile = "/home/sunghyki/Downloads/cub/map.cub";

	(void) ac;
	(void) av;
	(void) ti;
	init_tdir(&td);
	ti.td = &td;
	if (check_file(mapfile, &td, &ti) == -1)
		return (0);
	init_raycasting(&ti);
	free_all(&ti);
}
