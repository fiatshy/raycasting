/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:20:22 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/24 10:20:23 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	save_floor_ceiling(t_dir *td, int index, char **split_value)
{
	int	i;
	int	mult;

	i = 0;
	mult = 256 * 256;
	td->fc_value[index] = 0;
	while (split_value[i])
	{
		if (check_digit_format(split_value[i]) == -1)
		{
			printf("config error: Wrong digit format\n");
			free_split(split_value);
			return (-1);
		}
		td->fc_value[index] += (ft_atoi(split_value[i]) * mult);
		mult /= 256;
		i++;
	}
	return (0);
}

int	handle_floor_ceiling(char *s, int index, t_dir *td)
{
	char	**split_cat;
	char	**split_value;

	split_cat = ft_split(s, ' ');
	split_value = ft_split(split_cat[1], ',');
	free_split(split_cat);
	if (check_split_length(split_value) == -1 \
		|| save_floor_ceiling(td, index, split_value) == -1)
		return (-1);
	free_split(split_value);
	return (0);
}

int	handle_fc_error(t_dir *td, int i, char *temp)
{
	if (ft_strncmp(td->fc[i], temp, 1) == 0)
	{
		if (handle_floor_ceiling(temp, i, td) == -1)
		{
			free(temp);
			return (-1);
		}
	}
	else
	{
		free(temp);
		printf("config error: Wrong config name(floor and ceiling)\n");
		return (-1);
	}
	return (0);
}

int	check_floor_ceiling(int fd, t_dir *td)
{
	int		i;
	char	*temp;

	i = -1;
	temp = get_next_line(fd);
	while (++i < 2)
	{
		if (handle_fc_error(td, i, temp) == -1)
			return (-1);
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	return (0);
}
