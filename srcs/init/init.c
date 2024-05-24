/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:21:12 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/24 10:21:14 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_tdir(t_dir *td)
{
	td->dir = malloc (sizeof(char *) * 4);
	td->dir[0] = malloc (3);
	ft_memcpy(td->dir[0], "NO", 3);
	td->dir[1] = malloc (3);
	ft_memcpy(td->dir[1], "SO", 3);
	td->dir[2] = malloc (3);
	ft_memcpy(td->dir[2], "WE", 3);
	td->dir[3] = malloc (3);
	ft_memcpy(td->dir[3], "EA", 3);
	td->dir_path = malloc (sizeof(char *) * 4);
	td->fc = malloc (sizeof(char *) * 2);
	td->fc[0] = malloc (2);
	ft_memcpy(td->fc[0], "F", 2);
	td->fc[1] = malloc (2);
	ft_memcpy(td->fc[1], "C", 2);
}
