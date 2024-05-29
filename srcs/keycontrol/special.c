/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:49:17 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/29 08:49:18 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	key_space(t_info *ti)
{
	if (ti->map[(int)(ti->tv->arr_pos[1] + ti->tv->dir[1] * 1)][(int) \
				(ti->tv->arr_pos[0] + ti->tv->dir[0] * 1)] == 2)
	{
		ti->map[(int)(ti->tv->arr_pos[1] + ti->tv->dir[1] * 1)][(int) \
		(ti->tv->arr_pos[0] + ti->tv->dir[0] * 1)] += 1;
	}
}
