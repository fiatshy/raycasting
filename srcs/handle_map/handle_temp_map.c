/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_temp_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:21:29 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/24 10:21:31 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	handle_map_value(char *temp, int i, int temp_map[100][100])
{
	int	j;

	j = 0;
	while (*(temp + j))
	{
		if ('0' <= *(temp + j) && *(temp + j) <= '9')
			*(temp + j) -= '0';
		else if (check_if_map_direction(*(temp + j)))
			*(temp + j) -= 'A';
		else if ((9 <= *(temp + j) && *(temp + j) <= 13) || *(temp + j) == 32)
			*(temp + j) = -1;
		else
			return (-1);
		temp_map[i + 1][j + 1] = *(temp + j);
		j++;
	}
	return (0);
}

int	make_temp_map(int fd, int temp_map[100][100])
{
	char	*temp;
	int		i;

	temp = get_next_line(fd);
	i = 0;
	while (temp)
	{
		if (handle_map_value(temp, i, temp_map) == -1)
		{
			printf("map error: not allowed value.");
			free(temp);
			return (-1);
		}
		free(temp);
		temp = get_next_line(fd);
		i++;
	}
	return (0);
}

int	inspect_map_info(int temp_map[100][100], t_info *ti)
{
	ti->arr_height = check_rows(temp_map);
	ti->arr_width = check_cols(temp_map, ti);
	return (0);
}

int	handle_map(int fd, t_info *ti)
{
	int		temp_map[100][100];

	(void) ti;
	ft_memset(temp_map, -1, sizeof(int) * 100 * 100);
	if (make_temp_map(fd, temp_map) == -1)
		return (-1);
	if (check_map_error(ti, temp_map) == -1)
		return (-1);
	return (0);
}
