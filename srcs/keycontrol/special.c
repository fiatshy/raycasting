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
