#include "cub.h"

void	fill_background(t_info *ti)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			put_pixel(ti->tx->img, j, i, ti->td->fc_value[0]);
			j++;
		}
		i++;
	}
}

void	fill_ceiling(t_info *ti)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_HEIGHT / 2)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			put_pixel(ti->tx->img, j, i, ti->td->fc_value[1]);
			j++;
		}
		i++;
	}
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	render_frame(void *data)
{
	t_info	*ti;

	ti = data;
	fill_background(ti);
	fill_ceiling(ti);
	calculate_distance(ti);
	mlx_put_image_to_window(ti->tx->mlx, ti->tx->mlx_win, \
		ti->tx->img->img, 0, 0);
	return (0);
}
