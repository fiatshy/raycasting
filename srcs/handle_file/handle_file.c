/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:20:19 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/24 10:20:34 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_rows(int temp_map[100][100])
{
	int	i;
	int	j;
	int	one_flag;

	i = 1;
	j = 1;
	while (i < 100)
	{
		j = 0;
		one_flag = 0;
		while (j < 100)
		{
			if (temp_map[i][j] == 1)
				one_flag = 1;
			j++;
		}
		if (one_flag == 0)
			return (i);
		i++;
	}
	return (0);
}

int	check_cols(int temp_map[100][100], t_info *ti)
{
	int	i;
	int	j;
	int	cur_cols;
	int	max_cols;

	i = 1;
	j = 1;
	max_cols = 0;
	while (i < ti->arr_height)
	{
		j = 0;
		cur_cols = 0;
		while (j < 100)
		{
			if (temp_map[i][j] == 1)
				cur_cols = j;
			j++;
		}
		if (cur_cols > max_cols)
			max_cols = cur_cols;
		i++;
	}
	return (max_cols + 1);
}

int	check_cub_extension(char *s)
{
	char	**split;

	if (s == 0)
		return (-1);
	split = ft_split(s, '.');
	if (ft_strncmp("cub", split[1], 4) == 0)
	{
		free_split(split);
		return (1);
	}
	free_split(split);
	return (-1);
}

int	check_if_map_direction(char c)
{
	if (c == 'N')
		return (1);
	else if (c == 'S')
		return (1);
	else if (c == 'W')
		return (1);
	else if (c == 'E')
		return (1);
	return (0);
}

int	check_file(char	*mapfile, t_dir *td, t_info *ti)
{
	int		fd;

	if (check_cub_extension(mapfile) == -1)
	{
		printf("file error: only cub file extenstion is allowed\n");
		return (-1);
	}
	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
	{
		printf("file error: doesn't exist\n");
		return (-1);
	}
	if (handle_texture(fd, td) == -1)
		return (-1);
	if (handle_map(fd, ti) == -1)
		return (-1);
	return (0);
}
