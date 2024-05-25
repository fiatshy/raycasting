#include "cub.h"

void	draw_sprite_inner(t_calc_sprite *cs, t_info *ti, int x)
{
	int	y;

	y = cs->draw_start_y;
	while (y < cs->draw_end_y)
	{
		cs->d = (y - cs->v_move_screen) - \
			SCREEN_HEIGHT * 1 / 2 + cs->sprite_height * 1 / 2;
		cs->tex_y = ((cs->d * TEXTURE_HEIGHT) / cs->sprite_height);
		cs->color = ti->tx->tex->texture_addr[1][TEXTURE_WIDTH \
			* cs->tex_y + cs->tex_x];
		if ((cs->color & 0x00FFFFFF) != 0)
			put_pixel(ti->tx->img, x, y, cs->color);
		y++;
	}
}

void	draw_sprite(t_calc_sprite *cs, t_info *ti)
{
	int	x;

	x = cs->draw_start_x;
	while (x < cs->draw_end_x)
	{
		cs->tex_x = (int)((x - (-cs->sprite_width / 2 \
			+ cs->sprite_screen_x)) * TEXTURE_WIDTH / cs->sprite_width);
		if (cs->transform_y > 0 && \
			cs->transform_y < ti->tx->tex->dist_buffer[x])
			draw_sprite_inner(cs, ti, x);
		x++;
	}
}
