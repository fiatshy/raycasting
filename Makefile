TARGET = cub3d
CC	= gcc
FLAGS = -Wall -Wextra -Werror -g
FLAG_BONUS = 0

H = $(addprefix -I, $(HEADER_DIR))
HEADER_DIR = ./includes/
HEADER = ./includes/cub.h 

SRCS_DIR = ./srcs/

SRCS_FILE = cub.c \

SRCS_GNL = gnl/get_next_line.c \
			gnl/get_next_line_utils.c \

SRCS_HANDLE_FILE = 	handle_file/handle_file.c \
					handle_file/handle_floor_ceiling.c \
					handle_file/handle_texture.c \

SRCS_INIT = init/init.c \

SRCS_UTIL = util/util_file_handle.c \
			util/util_free.c \

SRCS_LIST = $(SRCS_FILE) \
			$(SRCS_GNL) \
			$(SRCS_HANDLE_FILE) \
			$(SRCS_INIT) \
			$(SRCS_UTIL) \

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR	= ./objs/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

LIBFT_PATH = ./srcs/libft/

.PHONY: all clean fclean re bonus

all: $(TARGET)

$(TARGET): $(OBJS)
	@ make -C $(LIBFT_PATH)
	@ $(CC) $(FLAGS) $(H) $^ -D BONUS=$(FLAG_BONUS) -o $@ $(LIBFT_PATH)libft.a -lreadline

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(FLAGS) $(H) -c -o $@ $<

bonus:
	@ $(MAKE) all FLAG_BONUS=1

clean:
	@ rm -rf $(OBJS_DIR)
	@ make clean -C $(LIBFT_PATH)

fclean: clean
	@ rm -f $(TARGET)
	@ make fclean -C $(LIBFT_PATH)

re: fclean all
