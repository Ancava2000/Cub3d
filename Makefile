# Colors
# ------
HOT_PINK			=	\033[38;5;169m
ITALIC				=	\033[3m
BOLD 				=	\033[1m
DEF_COLOR 			=	\033[0;39m
# ------

# Flags
# -------
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCDIR)/MLX42/include
LDFLAGS = -L$(MLXDIR)/build -lmlx42 -lglfw -ldl -lm -pthread
# -------

# Directories
# -------
SRCDIR = src
INCDIR = include
LIBFTDIR = $(INCDIR)/libft
MLXDIR = $(INCDIR)/MLX42

OBJ_DIR			= $(SRCDIR)/obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/build/libmlx42.a
# -------

# Sources
# -------
SRC = $(SRCDIR)/main.c \
		$(SRCDIR)/parse/parse.c \
		$(SRCDIR)/parse/parse_textures.c \
		$(SRCDIR)/parse/parse_utils.c \
		$(SRCDIR)/parse/parse_colors.c \
		$(SRCDIR)/parse/list_textures.c \
		$(SRCDIR)/parse/list_colors.c \
		$(SRCDIR)/parse/parse_map.c \
		$(SRCDIR)/parse/parse_map_utils.c \
		$(SRCDIR)/executor/mlx_init.c \
		$(SRCDIR)/executor/raycast.c \
		$(SRCDIR)/error_msg.c
# -------

# Main compilation
# -------
NAME = cub3D
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
# -------

# Libft compilation
# -------
$(LIBFT):
	@echo "$(HOT_PINK)$(BOLD) Compiling libft...$(DEF_COLOR)"
	@make -C $(LIBFTDIR)
	@echo "$(HOT_PINK)$(BOLD) libft.a and OBJS created ✓$(DEF_COLOR)"
# -------

# MLX42 compilation
# -------
$(MLX):
	@make -C $(MLXDIR)
# -------

# Clean
# -------
clean:
	@make clean -C $(LIBFTDIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(HOT_PINK)$(BOLD)Obj dir cub3d clean!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)
	@echo "$(HOT_PINK)$(BOLD)$(NAME) clean!$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re