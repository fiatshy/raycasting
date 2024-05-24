/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_floor_ceiling_util.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:20:24 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/24 10:20:25 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_split_length(char **split_value)
{
	if (get_split_length(split_value) != 3)
	{
		printf("config error: 3 digit is allowed for floor and ceiling value\n");
		free_split(split_value);
		return (-1);
	}
	return (0);
}

int	check_digit_format(char *s)
{
	while (*s)
	{
		if (*s != '\n' && ('0' > *s || *s > '9'))
		{
			return (-1);
		}
		s++;
	}
	return (0);
}
