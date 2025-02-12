NAME =			miniRT

SRC_DIR =		srcs
OBJ_DIR =		objs
LIBFT_DIR =		libft
MLX_DIR =		minilibx-linux
INC_DIR =		includes

LIBFT_REPO =	git@github.com:masakikaihori/libft.git
MLX_REPO =		git@github.com:42Paris/minilibx-linux.git

LIBFT_LIB =		$(LIBFT_DIR)/libft.a
MLX_LIB =		$(MLX_DIR)/mlx.a

SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC =		cc
CFLAGS =	-Wall -Werror -Wextra

all:$(LIBFT_LIB) $(MLX_LIB) $(NAME)

$(LIBFT_LIB):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning libft..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR); \
	fi
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning mlx..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	$(MAKE) -C $(MLX_DIR)

bonus:all

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean:clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) fclean
	rm -f $(NAME)

repoclean:
	rm -rf $(LIBFT_DIR)
	rm -rf $(MLX_DIR)

re:fclean all

.PHONY: all bonus clean fclean re