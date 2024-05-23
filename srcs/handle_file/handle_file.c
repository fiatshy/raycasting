#include "cub.h"

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

int	check_rows(int	temp_map[100][100])
{
	int	i;
	int	j;
	int	one_flag;

	i = 0;
	j = 0;
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

	i = 0;
	j = 0;
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

int	inspect_map_info(int temp_map[100][100], t_info *ti)
{
	ti->arr_height = check_rows(temp_map);
	ti->arr_width = check_cols(temp_map, ti);
	return (0);
}

void	get_first_and_last_index(t_info *ti, int row, int temp_map[100][100], t_check *tc)
{
	int	i;
	int	first_time;

	i = 0;
	first_time = 1;
	while (i < ti->arr_width)
	{
		if (temp_map[row][i] == 1)
		{
			if (first_time == 1)
			{
				first_time = 0;
				tc->first = i;
			}
			tc->last = i;
		}
		i++;
	}
}

int	progress_left(t_info *ti, t_check *tc, int temp_map[100][100])
{
	int	i;
	int	j;
	int	error;

	(void) ti;
	i = tc->row;
	j = tc->col;
	error = 1;
	while (j >= tc->first)
	{
		if (temp_map[i][j] == 1)
			error = 0;
		j--;
	}
	if (error == 1)
		return (-1);
	return (0);
}

int	progress_rows(t_info *ti, int temp_map[100][100])
{
	int		i;
	int		j;
	t_check	*tc;

	(void) ti;
	tc = malloc (sizeof(t_check));
	i = 0;
	while (i < 1)
	{
		get_first_and_last_index(ti, i, temp_map, tc);
		j = tc->first;
		while (j < tc->last)
		{
			tc->row = i;
			tc->col = j;
			printf("%d\n", progress_left(ti, tc, temp_map));
			j++;
		}
		i++;
	}
	return (0);
}

int check_border_rows(t_info *ti, int temp_map[100][100])
{
	if (progress_rows(ti, temp_map) == -1)
		return (-1);
	return (0);
}

int	check_map_error(t_info *ti, int temp_map[100][100])
{
	inspect_map_info(temp_map, ti);
	if (check_border_rows(ti, temp_map) == - 1)
		return (-1);
	return (0);	
}

int	handle_map(int fd, t_info *ti)
{
	int		temp_map[100][100];

	(void) ti;
	ft_memset(temp_map, -1, sizeof(int) * 100 * 100);
	if (make_temp_map(fd, temp_map) == -1)
		return (-1);
	for (int i = 0; i < 99; i++)
	{
		for (int j = 0; j < 99; j++)
		{
			printf("%d", temp_map[i][j]);
		}
		printf("\n");
	}
	if (check_map_error(ti, temp_map) == -1)
		return (-1);
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