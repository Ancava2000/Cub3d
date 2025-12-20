ITALIC =		\033[3m
DEF_COLOR =		\033[0;39m
CYAN_2 =        \033[38;5;50m

NAME			= libft.a

SRC = ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
\
get_next_line_utils.c \
get_next_line.c \
\
ft_skipspace.c \
ft_isspace.c \

BSRC = ft_lstadd_back_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstclear_bonus.c \
ft_lstdelone_bonus.c \
ft_lstiter_bonus.c \
ft_lstlast_bonus.c \
ft_lstmap_bonus.c \
ft_lstnew_bonus.c \
ft_lstsize_bonus.c \

OBJ_DIR			= obj
OBJS			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
BOBJS			= $(addprefix $(OBJ_DIR)/, $(BSRC:.c=.o))

CC				= gcc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -I.

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				@ar rcs $(NAME) $(OBJS)
				@echo "$(CYAN_2)$(ITALIC)Obj dir created!$(DEF_COLOR)"
				@echo "$(CYAN_2)$(ITALIC)$(NAME) created!$(DEF_COLOR)"

bonus:			$(NAME) $(OBJS) $(BOBJS)
					@ar rcs $(NAME) $(OBJS) $(BOBJS)
					@echo "Bonus created!"

clean:
				@$(RM) $(OBJ_DIR)
				@echo "$(CYAN_2)$(ITALIC)Obj dir libft clean!$(DEF_COLOR)"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(CYAN_2)$(ITALIC)$(NAME) clean!$(DEF_COLOR)"

re:				fclean all

.PHONY:			all clean fclean re bonus
