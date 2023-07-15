NAME = fdf
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = fdf fdf_window_management fdf_colors fdf_draw fdf_process_map fdf_transform_map fdf_utils
LIBFT = libft.a
INCLUDE = -I/usr/include -Imlx_linux -O3
LIBS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
	
all: $(NAME)

%.o: %.c
	@$(MAKE) -C mlx_linux
	@echo "libmlx.a compiled"
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c $< -o $@

$(NAME): $(LIBFT) $(SRC:=.o)
	$(CC) $(SRC:=.o) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C libft bonus
	@cp libft/libft.a .
	@cp libft/libft.h .
	@echo "libft.a compiled and imported"

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	rm -f libft.a
	rm -f libft.h
ifneq (,$(wildcard libft/))
	$(MAKE) -C libft fclean
endif

re: fclean all

.PHONY: clean fclean re all