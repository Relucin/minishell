INCLUDES	+= minishell ms_builtina ms_builtinb
INCLUDES	+= ms_path ms_helpers
INCLUDES	:= $(addprefix src/, $(INCLUDES))
INCLUDES	:= $(addsuffix .o, $(INCLUDES))
CC			:= gcc
FLAGS		+= -Wall -Wextra -Werror -Ilibft/include/ -Iinclude/
# FLAGS		+= -g
NAME		:= minishell

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(INCLUDES) libft/libftprintf.a
	@echo 'Building $(NAME)'
	@$(CC) $(FLAGS) $^ -o $@

%.o: %.c
	@$(CC) $(FLAGS) -c $^ -o $@

libft/libftprintf.a:
	@make -C libft/

clean:
	@echo 'Removing $(NAME)--object files'
	@rm -rf $(INCLUDES)
	@make -C libft/ clean

fclean: clean
	@echo 'Removing $(NAME)'
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all
