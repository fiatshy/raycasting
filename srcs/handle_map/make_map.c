/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:37:42 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/27 13:37:44 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_map(int temp_map[100][100], t_info *ti)
{
	int	i;
	int	j;

	i = 1;
	while (i < ti->arr_height)
	{
		j = 1;
		while (j < ti->arr_width)
		{
			if (temp_map[i][j] == -1)
				ti->map[i - 1][j - 1] = 0;
			else
				ti->map[i - 1][j - 1] = temp_map[i][j];
			j++;
		}
		i++;
	}
	ti->arr_height -= 1;
	ti->arr_width -= 1;
}

void	make_map(int temp_map[100][100], t_info *ti)
{
	int	i;

	ti->map = malloc (sizeof(int *) * (ti->arr_height - 1));
	i = 0;
	while (i < ti->arr_height - 1)
	{
		ti->map[i] = malloc (sizeof(int) * (ti->arr_width - 1));
		i++;
	}
	init_map(temp_map, ti);
}
