CC = cc

NAME = cub

CFLAGS = -Wall -Wextra -Werror

MLXF = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm

SRC = src/main.c src/parsing/get_next_line.c  src/parsing/ft_splite.c \
		src/parsing/read_map_utils.c src/parsing/garbage_collector.c \
		src/raycast/key_press.c src/raycast/raycaster.c src/raycast/key_press_utils.c\
		src/raycast/texturing.c src/raycast/raycaster_utils.c\
		src/parsing/minimap.c src/parsing/p_utils_t.c src/parsing/parse_map.c\
		src/parsing/full_map.c src/parsing/p_texture_color.c src/parsing/parse_cub.c\
		src/parsing/parse_utils.c src/raycast/init_p.c src/parsing/read_map_utils1.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLXF) -o $(NAME)
	@echo "ALL IS GOOD :/\:"

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all bonus clean fclean re
.SECONDARY:
