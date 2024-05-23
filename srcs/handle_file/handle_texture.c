#include "cub.h"

int	copy_texture_path(char *temp, int i, t_dir *td)
{
	char	**split_path;
	int		cpy_length;

	split_path = ft_split(temp, ' ');
	if (get_split_length(split_path) != 2)
	{
		printf("texture needs only 2 value");
		return (-1);
	}
	if (split_path[1] == NULL)
	{
		printf("texture path is null\n");
		free_split(split_path);
		return (-1);
	}
	cpy_length = ft_strlen(split_path[1]);
	td->dir_path[i] = malloc (cpy_length + 1);
	ft_memcpy(td->dir_path[i], split_path[1], cpy_length + 1);
	free_split(split_path);
	return (0);
}

int	check_config_texture_name(int fd, t_dir *td)
{
	int		i;
	char	*temp;

	i = -1;
	temp = get_next_line(fd);
	while (++i < 4)
	{
		if (ft_strncmp(td->dir[i], temp, 2) == 0)
		{
			if (copy_texture_path(temp, i, td) == -1)
				return (-1);
		}
		else
		{
			free(temp);
			printf("config error: Wrong direction name\n");
			return (-1);
		}
		free(temp);
		temp = get_next_line(fd);
	}
	return (0);
}

int	handle_texture(int fd, t_dir *td)
{
	if (check_config_texture_name(fd, td) == -1)
		return (-1);
	if (check_floor_ceiling(fd, td) == -1)
		return (-1);
	return (0);
}