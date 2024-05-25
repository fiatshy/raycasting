#include "cub.h"

void	init_doors_nested(t_info *ti)
{
	int			xpm_width;
	int			xpm_height;
	t_img		temp;

	ti->tx->tex->texture_ptr[4] = mlx_xpm_file_to_image(\
			ti->tx->mlx, "./srcs/texture/door_b.xpm", \
			&xpm_width, &xpm_height);
	ti->tx->tex->texture_addr[4] = (int *) mlx_get_data_addr(\
			ti->tx->tex->texture_ptr[4], \
			&temp.bits_per_pixel, &temp.line_length, &temp.endian);
	ti->tx->tex->texture_ptr[5] = mlx_xpm_file_to_image(\
			ti->tx->mlx, "./srcs/texture/door_c.xpm", \
			&xpm_width, &xpm_height);
	ti->tx->tex->texture_addr[5] = (int *) mlx_get_data_addr(\
			ti->tx->tex->texture_ptr[5], \
			&temp.bits_per_pixel, &temp.line_length, &temp.endian);
}

void	init_doors(t_info *ti)
{
	int			xpm_width;
	int			xpm_height;
	t_img		temp;

	ti->tx->tex->texture_ptr[2] = mlx_xpm_file_to_image(\
			ti->tx->mlx, "./srcs/texture/door.xpm", \
			&xpm_width, &xpm_height);
	ti->tx->tex->texture_addr[2] = (int *) mlx_get_data_addr(\
			ti->tx->tex->texture_ptr[2], \
			&temp.bits_per_pixel, &temp.line_length, &temp.endian);
	ti->tx->tex->texture_ptr[3] = mlx_xpm_file_to_image(\
			ti->tx->mlx, "./srcs/texture/door_a.xpm", \
			&xpm_width, &xpm_height);
	ti->tx->tex->texture_addr[3] = (int *) mlx_get_data_addr(\
			ti->tx->tex->texture_ptr[3], \
			&temp.bits_per_pixel, &temp.line_length, &temp.endian);
	init_doors_nested(ti);
}
