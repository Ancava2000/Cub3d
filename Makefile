# Nombre del ejecutable
NAME = cub3D

# Compilador y flags
CC = clang
CFLAGS = -Wall -Wextra -Werror -g

# Directorios
SRCDIR = src
INCDIR = include
LIBFTDIR = $(INCDIR)/libft
MLXDIR = $(INCDIR)/minilibx

# Archivos fuente
SRC = $(SRCDIR)/main.c \
		$(SRCDIR)/parse/parse.c \
		$(SRCDIR)/parse/parse_textures.c \
		$(SRCDIR)/parse/parse_utils.c \
		$(SRCDIR)/parse/parse_colors.c \
		$(SRCDIR)/parse/list_textures.c \
		$(SRCDIR)/parse/list_colors.c \
		$(SRCDIR)/error_msg.c

# Archivos objeto
OBJ = $(SRC:.c=.o)

# Librerías
LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/libmlx.a

# Comandos
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lX11 -lXext -lm -lbsd

$(LIBFT):
	@make -C $(LIBFTDIR)

$(MLX):
	@make -C $(MLXDIR)

clean:
	@rm -f $(OBJ)
	@make clean -C $(LIBFTDIR)
	@make clean -C $(MLXDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re