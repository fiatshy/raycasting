#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"

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

typedef struct s_info
{
	int		**map;
	t_dir	*td;
	t_check	*tc;
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

/* init */
void	init_tdir(t_dir *td);

/* free */
void	free_split(char **split);

#endif