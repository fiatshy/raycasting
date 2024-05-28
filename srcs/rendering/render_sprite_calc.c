/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_calc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:37:05 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/27 13:37:09 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calc_sprite_transform(t_calc_sprite *cs, t_info *ti, int i)
{
	cs->sprite_x = ti->tx->tex->sprite[ti->tx->tex->sprite_order[i]].x \
			- ti->tv->arr_pos[0];
	cs->sprite_y = ti->tx->tex->sprite[ti->tx->tex->sprite_order[i]].y \
			- ti->tv->arr_pos[1];
	cs->inv_det = 1.0 / (ti->tv->plane[0] * ti->tv->dir[1] \
			- ti->tv->dir[0] * ti->tv->plane[1]);
	cs->transform_x = cs->inv_det * (ti->tv->dir[1] * cs->sprite_x \
			- ti->tv->dir[0] * cs->sprite_y);
	cs->transform_y = cs->inv_det * (-ti->tv->plane[1] * cs->sprite_x \
			+ ti->tv->plane[0] * cs->sprite_y);
}

void	calc_sprite_y(t_calc_sprite *cs)
{
	cs->sprite_screen_x = (int)((SCREEN_WIDTH / 2) \
			* (1 + cs->transform_x / cs->transform_y));
	cs->v_move_screen = (int)(V_MOVE / cs->transform_y);
	cs->h = SCREEN_HEIGHT;
	cs->sprite_height = abs((int)(SCREEN_HEIGHT / (cs->transform_y))) \
			/ V_DIV;
	cs->draw_start_y = -cs->sprite_height / 2 + SCREEN_HEIGHT / 2 \
			+ cs->v_move_screen;
	if (cs->draw_start_y < 0)
		cs->draw_start_y = 0;
	cs->draw_end_y = cs->sprite_height / 2 + SCREEN_HEIGHT / 2 \
			+ cs->v_move_screen;
	if (cs->draw_end_y >= SCREEN_HEIGHT)
		cs->draw_end_y = SCREEN_HEIGHT - 1;
}

void	calc_sprite_x(t_calc_sprite *cs)
{
	cs->sprite_width = abs((int)(SCREEN_HEIGHT / (cs->transform_y))) \
			/ U_DIV;
	cs->draw_start_x = -cs->sprite_width / 2 + cs->sprite_screen_x;
	if (cs->draw_start_x < 0)
		cs->draw_start_x = 0;
	cs->draw_end_x = cs->sprite_width / 2 + cs->sprite_screen_x;
	if (cs->draw_end_x > SCREEN_WIDTH)
		cs->draw_end_x = SCREEN_WIDTH;
}

void	transform_sprite(t_info *ti)
{
	int				i;
	t_calc_sprite	*cs;

	cs = malloc (sizeof(t_calc_sprite));
	i = 0;
	while (i < NUMBER_OF_SPRITES)
	{
		calc_sprite_transform(cs, ti, i);
		calc_sprite_y(cs);
		calc_sprite_x(cs);
		draw_sprite(cs, ti);
		i++;
	}
}

void	calculate_distance(t_info *ti)
{
	int			x;
	t_distance	td;
	t_wall		tw;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		caclulate_distance_prepare(ti, &td, x);
		calculate_initial_distance(ti, &td);
		calculate_distance_hit(ti, &td, x);
		calculate_draw_value(ti, &tw, &td);
		draw_texture(ti, &tw, &td, x);
		caclulate_distance_prepare(ti, &td, x);
		calculate_initial_distance(ti, &td);
		calculate_distance_hit_test(ti, &td, x);
		calculate_draw_value(ti, &tw, &td);
		draw_texture(ti, &tw, &td, x);
		x++;
	}
	order_by_distance(ti);
	transform_sprite(ti);
}
