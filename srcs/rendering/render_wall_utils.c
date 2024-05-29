/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:49:35 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/29 08:49:37 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	select_wall_color(t_wall *tw, t_info *ti, t_distance *td, int value)
{
	if (value == 1)
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
	else if (value > 1)
	{
		tw->color = ti->tx->tex->texture_addr[value][TEXTURE_HEIGHT \
				* tw->tex_y + tw->tex_x];
	}
}
