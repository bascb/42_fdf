NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = fdf
LIBFT = libft.a
INCLUDE = -I/usr/include -Imlx_linux
LIBS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
	
all: $(NAME)

$(NAME): $(LIBFT) $(SRC:=.o)
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o $(NAME) $(SRC:=.o) $(LIBFT)
	
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