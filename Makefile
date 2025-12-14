HOT_PINK			=	\033[38;5;169m

NAME = cub3D

CC = clang
CFLAGS = -Wall -Wextra -Werror -g

SRCDIR = src
INCDIR = include
LIBFTDIR = $(INCDIR)/libft
MLXDIR = $(INCDIR)/minilibx

SRC = $(SRCDIR)/main.c \
		$(SRCDIR)/parse/parse.c \
		$(SRCDIR)/parse/parse_textures.c \
		$(SRCDIR)/parse/parse_utils.c \
		$(SRCDIR)/parse/parse_colors.c \
		$(SRCDIR)/parse/list_textures.c \
		$(SRCDIR)/parse/list_colors.c \
		$(SRCDIR)/parse/parse_map.c \
		$(SRCDIR)/error_msg.c

OBJ_DIR			= $(SRCDIR)/obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lX11 -lXext -lm -lbsd
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
	@make -C $(MLXDIR)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFTDIR)
	@make clean -C $(MLXDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re