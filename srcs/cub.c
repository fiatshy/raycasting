#include "cub.h"

int	main(int ac, char **av)
{
	t_dir	td;
	t_info 	ti;
	char	*mapfile = "/home/sunghyki/Downloads/cub/map.cub";

	(void) ac;
	(void) av;
	(void) ti;
	//if	(ac != 2)
	//	return (0);
	init_tdir(&td);
	if (check_file(mapfile, &td, &ti) == -1)
		return (0);
}