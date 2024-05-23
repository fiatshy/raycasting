#include "cub.h"

int	get_split_length(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		;
	return (i);
}