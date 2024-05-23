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

/* handle_texture */
int		copy_texture_path(char *temp, int i, t_dir *td);
int		check_config_texture_name(int fd, t_dir *td);
int		handle_texture(int fd, t_dir *td);

/* handle_file */
int		check_cub_extension(char *s);
int		check_file(char	*mapfile, t_dir *td, t_info *ti);

/* init */
void	init_tdir(t_dir *td);

/* free */
void	free_split(char **split);

#endif