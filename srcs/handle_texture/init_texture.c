/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:38:04 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/27 13:38:07 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_walls(t_info *ti)
{
	int			xpm_width;
	int			xpm_height;
	t_img		temp;
	char		*trim_string;
	int			i;

	i = 0;
	while (i < 4)
	{
		trim_string = ft_strtrim(ti->td->dir_path[i], "\n");
		ti->tx->tex->wall_ptr[i] = mlx_xpm_file_to_image(\
				ti->tx->mlx, trim_string, &xpm_width, &xpm_height);
		free(trim_string);
		ti->tx->tex->wall_addr[i] = (int *) mlx_get_data_addr(\
				ti->tx->tex->wall_ptr[i], &temp.bits_per_pixel, \
				&temp.line_length, &temp.endian);
		i++;
	}
}

void	init_texture(t_info *ti)
{
	int			xpm_width;
	int			xpm_height;
	t_img		temp;

	ti->tx->tex->texture_ptr[0] = NULL;
	ti->tx->tex->texture_addr[0] = NULL;
	ti->tx->tex->texture_ptr[1] = mlx_xpm_file_to_image(\
			ti->tx->mlx, "./srcs/texture/greenlight.xpm", \
			&xpm_width, &xpm_height);
	ti->tx->tex->texture_addr[1] = (int *) mlx_get_data_addr(\
			ti->tx->tex->texture_ptr[1], \
			&temp.bits_per_pixel, &temp.line_length, &temp.endian);
	init_doors(ti);
}

void	init_xpm(t_info *ti)
{
	t_texture	*tex;

	tex = malloc (sizeof(t_texture));
	ti->tx->tex = tex;
	ti->tx->tex->wall_ptr = malloc (sizeof(void *) * 4);
	ti->tx->tex->wall_addr = malloc (sizeof(int *) * 4);
	ti->tx->tex->texture_ptr = malloc (sizeof(void *) * 6);
	ti->tx->tex->texture_addr = malloc (sizeof(int *) * 6);
	ti->tx->tex->count = 0;
	init_walls(ti);
	init_texture(ti);
	init_config(ti);
	init_mlx_config(ti);
}

void	init_raycasting(t_info *ti)
{
	t_mlx	*tx;
	t_img	*tmg;

	tx = malloc (sizeof(t_mlx));
	tmg = malloc (sizeof(t_img));
	tx->mlx = mlx_init();
	tx->mlx_win = mlx_new_window(tx->mlx, \
		SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	tmg->img = mlx_new_image(tx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	tmg->addr = mlx_get_data_addr(tmg->img, \
		&tmg->bits_per_pixel, &tmg->line_length, &tmg->endian);
	tx->img = tmg;
	ti->tx = tx;
	init_xpm(ti);
}
