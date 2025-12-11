HOT_PINK			=	\033[38;5;169m

NAME = cub3D

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -I$(INCDIR)/MLX42/include
LDFLAGS = -L$(MLXDIR)/build -lmlx42 -lglfw -ldl -lm -pthread

SRCDIR = src
INCDIR = include
LIBFTDIR = $(INCDIR)/libft
MLXDIR = $(INCDIR)/MLX42

SRC = $(SRCDIR)/main.c \
		$(SRCDIR)/parse/parse.c \
		$(SRCDIR)/parse/parse_textures.c \
		$(SRCDIR)/parse/parse_utils.c \
		$(SRCDIR)/parse/parse_colors.c \
		$(SRCDIR)/parse/list_textures.c \
		$(SRCDIR)/parse/list_colors.c \
		$(SRCDIR)/executor/mlx_init.c \
		$(SRCDIR)/error_msg.c

OBJ_DIR			= $(SRCDIR)/obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/build/libmlx42.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(HOT_PINK)"
	@sleep 0.1
	@echo " ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
	@sleep 0.1
	@echo "██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@sleep 0.1
	@echo "██║     ██║   ██║██████╔╝ █████╔╝██║  ██║"
	@sleep 0.1
	@echo "██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@sleep 0.1
	@echo "╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝"
	@sleep 0.1
	@echo

$(LIBFT):
	@make -C $(LIBFTDIR)

$(MLX):
	@cmake -B $(MLXDIR)/build $(MLXDIR) > /dev/null 2>&1
	@cmake --build $(MLXDIR)/build -j4 > /dev/null 2>&1

clean:
	@make clean -C $(LIBFTDIR)
	@rm -rf $(MLXDIR)/build
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re