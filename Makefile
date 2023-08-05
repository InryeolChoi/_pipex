NAME = pipex
LIBFT_DIR = ./libft
CC = cc -g -Wall -Wextra -Werror #-fsanitize=address

SRCS_DIR = ./srcs
SRCS = pipex_main.c pipex_process.c \
		pipex_util.c pipex_error.c
OBJS = $(addprefix $(SRCS_DIR)/, $(SRCS:.c=.o))

BONUS_DIR = ./bonus
SRCS_BONUS = main_bonus.c process_bonus.c \
				util_bonus.c exit_bonus.c \
				child_bonus.c 
OBJS_BONUS = $(addprefix $(BONUS_DIR)/, $(SRCS_BONUS:.c=.o))

ifdef BONUS
	FIXED_OBJS = $(OBJS_BONUS)
else
	FIXED_OBJS = $(OBJS)
endif

all : $(NAME)

$(NAME) : $(FIXED_OBJS)
	make -C $(LIBFT_DIR) all
	$(CC) $(FIXED_OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

clean :
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re : fclean all

bonus : 
	make BONUS=1 all

.PHONY : all clean fclean re bonus