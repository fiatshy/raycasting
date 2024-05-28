#include "cub.h"

void	select_wall_color(t_wall *tw, t_info *ti, t_distance *td)
{
	if (td->ray_dir_y > 0 && td->side == 1)
		tw->color = ti->tx->tex->wall_addr[0][TEXTURE_HEIGHT \
			* tw->tex_y + tw->tex_x];
	else if (td->ray_dir_y < 0 && td->side == 1)
		tw->color = ti->tx->tex->wall_addr[1][TEXTURE_HEIGHT \
			* tw->tex_y + tw->tex_x];
	else if (td->ray_dir_x > 0 && td->side == 0)
		tw->color = ti->tx->tex->wall_addr[2][TEXTURE_HEIGHT \
			* tw->tex_y + tw->tex_x];
	else if (td->ray_dir_x < 0 && td->side == 0)
		tw->color = ti->tx->tex->wall_addr[3][TEXTURE_HEIGHT \
			* tw->tex_y + tw->tex_x];
}