# Makefile

NAME = cub3D
SRCS = ./src/cub3D.c ./src/init.c ./src/raycasting.c ./src/ft_putstr.c  ./src/utils.c  ./get_next/get_next_line.c ./get_next/get_next_line_utils.c

LIBS =  -L libft -lft 
OBJ = $(SRCS:.c=.o)
CC = cc #-fsanitize=address -g3
#CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -Lmlx_linux minilibx-linux/libmlx_Linux.a -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@echo "\033[1;cub3D objects are deleted"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "\033[1;31cub3D is deleted"

re: fclean all
