/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghyki <sunghyki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:37:11 by sunghyki          #+#    #+#             */
/*   Updated: 2024/05/27 13:37:13 by sunghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	sort_sprites_nested_b(int *order, double *dist, \
	int amount, struct s_pair *sprites)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

void	sort_sprites_nested(int *order, double *dist, \
	int amount, struct s_pair *sprites)
{
	int				i;
	int				j;
	struct s_pair	temp;

	i = 0;
	while (i < amount - 1)
	{
		j = 0;
		while (j < amount - i - 1)
		{
			if (sprites[j].first > sprites[j + 1].first)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	sort_sprites_nested_b(order, dist, amount, sprites);
}

void	sort_sprites(int *order, double *dist, int amount)
{
	struct s_pair	*sprites;
	int				i;

	sprites = (struct s_pair *) malloc (amount * sizeof(struct s_pair));
	if (sprites == NULL)
		return ;
	i = 0;
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_sprites_nested(order, dist, amount, sprites);
}

void	order_by_distance(t_info *ti)
{
	int	i;

	i = 0;
	while (i < NUMBER_OF_SPRITES)
	{
		ti->tx->tex->sprite_order[i] = i;
		ti->tx->tex->sprite_distance[i] = \
			((ti->tv->arr_pos[0] - ti->tx->tex->sprite[i].x) * \
			(ti->tv->arr_pos[0] - ti->tx->tex->sprite[i].x) + \
			(ti->tv->arr_pos[1] - ti->tx->tex->sprite[i].y) * \
			(ti->tv->arr_pos[1] - ti->tx->tex->sprite[i].y));
		i++;
	}
}
