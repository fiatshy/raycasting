#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define	UP						119
# define	DOWN					115
# define	LEFT					97
# define	RIGHT					100
# define	LEFT_ARROW				65361
# define	RIGHT_ARROW				65363
# define	TEXTURE_HEIGHT			64
# define	TEXTURE_WIDTH			64
# define	SCREEN_WIDTH			640
# define	SCREEN_HEIGHT			480
# define	NUMBER_OF_SPRITES		2

#define U_DIV 1
#define V_DIV 1
#define V_MOVE 0.0

typedef struct s_mini 
{
	int	startx;
	int	endx;
	int	starty;
	int	endy;
}				t_mini;

struct s_pair {
    double first;
    int second;
};

typedef struct s_calc_sprite
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double 	transform_y;
	int sprite_screen_x;
	int v_move_screen;
	int	h;
	int sprite_height;
	int draw_start_y;
	int draw_end_y;
	int sprite_width;
	int draw_start_x;
	int draw_end_x;
	int tex_x;
	int d;
	int tex_y;
	int color;
}				t_calc_sprite;

typedef struct s_prite
{
	double 	x;
	double 	y;
	int 	texture;
}		t_prite;

typedef struct s_texture
{
	void	**wall_ptr;
	int		**wall_addr;
	void	**texture_ptr;
	int		**texture_addr;
	t_prite	sprite[NUMBER_OF_SPRITES];
	int		sprite_order[NUMBER_OF_SPRITES];
	double	sprite_distance[NUMBER_OF_SPRITES];
	double	dist_buffer[SCREEN_WIDTH];
}			t_texture;

typedef struct s_view
{
	double	arr_pos[2];
	double	dir[2];
	double	plane[2];
}				t_view;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef	struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_img		*img;
	t_texture	*tex;
	int			*addr;
}				t_mlx;

typedef struct s_check
{
	int	first;
	int	last;
	int	row;
	int	col;
}				t_check;

typedef struct	s_dir
{
	char	**dir;
	char	**dir_path;
	char	**fc;
	int		fc_value[2];
}				t_dir;

typedef struct s_distance
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}				t_distance;

typedef	struct s_wall
{
	int		h;
	int		line_height;
	int		pitch;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;	
}				t_wall;

typedef struct s_info
{
	int		**map;
	t_dir	*td;
	t_check	*tc;
	t_mlx	*tx;
	t_view	*tv;
	int		arr_width;
	int		arr_height;
}				t_info;

/* util_file_handling */
int		get_split_length(char **split);

/* handle_floor_ceiling */
int		check_split_length(char **split_value);
int		check_digit_format(char *s);

int		save_floor_ceiling(t_dir *td, int index, char **split_value);
int		handle_floor_ceiling(char *s, int index, t_dir *td);
int		check_floor_ceiling(int fd, t_dir *td);
int		handle_fc_error(t_dir *td, int i, char *temp);

/* handle_texture */
int		copy_texture_path(char *temp, int i, t_dir *td);
int		check_config_texture_name(int fd, t_dir *td);
int		handle_texture(int fd, t_dir *td);

/* handle temp map */
int		handle_map_value(char *temp, int i, int temp_map[100][100]);
int		make_temp_map(int fd, int temp_map[100][100]);
int		inspect_map_info(int temp_map[100][100], t_info *ti);
int		handle_map(int fd, t_info *ti);

/* check_map_error */
int		check_surrounding_value(t_info *ti, int temp_map[100][100]);
int		progress_map_nested(t_info *ti, int temp_map[100][100], int i);
int		progress_map(t_info *ti, int temp_map[100][100]);
int		check_map_error(t_info *ti, int temp_map[100][100]);

/* handle_file */
int		check_rows(int temp_map[100][100]);
int		check_cols(int temp_map[100][100], t_info *ti);
int		check_if_map_direction(char c);
int		check_cub_extension(char *s);
int		check_file(char	*mapfile, t_dir *td, t_info *ti);

/* make_map */
void	make_map(int temp_map[100][100], t_info *ti);
void	init_map(int temp_map[100][100], t_info *ti);

/* init */
void	init_tdir(t_dir *td);

/* free */
void	free_split(char **split);

/* init_texture */
void	init_walls(t_info *ti);
void	init_texture(t_info *ti);
void	init_xpm(t_info *ti);
void	init_raycasting(t_info *ti);

/* init_doors */
void	init_doors(t_info *ti);
void	init_doors_nested(t_info *ti);

/* init_config */
void	init_config(t_info *ti);
void	init_mlx_config(t_info *ti);

/* rdeer_util */
double	abs_double(double x);

/* render_wall */
void	caclulate_distance_prepare(t_info *ti, t_distance *td, int x);
void	calculate_initial_distance(t_info *ti, t_distance *td);
void	calculate_distance_hit(t_info *ti, t_distance *td, int x);
void	calculate_draw_value(t_info *ti, t_wall *tw, t_distance *td);
void	draw_texture(t_info *ti, t_wall *tw, t_distance *td, int x);

/* render_sprite_utils */
void	sort_sprites_nested_b(int *order, double *dist, \
		int amount, struct s_pair *sprites);
void	sort_sprites_nested(int *order, double *dist, \
		int amount, struct s_pair *sprites);
void	sort_sprites(int *order, double *dist, int amount);
void	order_by_distance(t_info *ti);

/* render_sprite_calc */
void	calc_sprite_transform(t_calc_sprite *cs, t_info *ti, int i);
void	calc_sprite_y(t_calc_sprite *cs);
void	calc_sprite_x(t_calc_sprite *cs);
void	transform_sprite(t_info *ti);
void	calculate_distance(t_info *ti);

/* render_sprite_draw */
void	draw_sprite_inner(t_calc_sprite *cs, t_info *ti, int x);
void	draw_sprite(t_calc_sprite *cs, t_info *ti);


/* render_general */
void	put_pixel(t_img *img, int x, int y, int color);
void	fill_background(t_info *ti);
void	fill_ceiling(t_info *ti);
int		render_frame(void *data);

/* direction */
void	key_right(t_info *ti);
void	key_left(t_info *ti);
void	key_down(t_info *ti);
void	key_up(t_info *ti);

/* arrow */
void	key_right_arrow(t_info *ti);
void	key_left_arrows(t_info *ti);

void	free_all(t_info *ti);

void	fill_minimap_wall(t_info *ti);
void	fill_minimap(t_info *ti);
void	fill_wall(t_info *ti, t_mini tm);

#endif