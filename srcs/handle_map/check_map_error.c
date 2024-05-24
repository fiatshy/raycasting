/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:21:26 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/24 10:21:29 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_surrounding_value(t_info *ti, int temp_map[100][100])
{
	if (temp_map[ti->tc->row - 1][ti->tc->col] == -1)
		return (-1);
	else if (temp_map[ti->tc->row + 1][ti->tc->col] == -1)
		return (-1);
	else if (temp_map[ti->tc->row][ti->tc->col - 1] == -1)
		return (-1);
	else if (temp_map[ti->tc->row][ti->tc->col + 1] == -1)
		return (-1);
	return (0);
}

int	progress_map_nested(t_info *ti, int temp_map[100][100], int i)
{
	int	j;

	j = 0;
	while (j < ti->arr_width)
	{
		if (temp_map[i][j] == 0)
		{
			ti->tc->row = i;
			ti->tc->col = j;
			if (check_surrounding_value(ti, temp_map) == -1)
			{
				printf("map error: Map is not surrounded by wall\n");
				return (-1);
			}
		}
		j++;
	}
	return (0);
}

int	progress_map(t_info *ti, int temp_map[100][100])
{
	int		i;
	t_check	*tc;

	tc = malloc (sizeof(t_check));
	ti->tc = tc;
	i = 0;
	while (i < ti->arr_height)
	{
		if (progress_map_nested(ti, temp_map, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	check_map_error(t_info *ti, int temp_map[100][100])
{
	inspect_map_info(temp_map, ti);
	if (progress_map(ti, temp_map) == -1)
		return (-1);
	return (0);
}
