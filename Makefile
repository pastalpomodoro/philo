NAME=philo

CC=cc
FLAGS=-Wall -Wextra -Werror -g3 -fsanitize=thread
# FLAGS=-Wall -Wextra -Werror -g3

SRC=main.c \
	init_philo.c \
	utils.c \

OBJ_DIR=obj
OBJ=$(SRC:%.c=$(OBJ_DIR)/%.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
