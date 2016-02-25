NAME=lem-in

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= ft_creat_way_lem.c \
  ft_parssing_lem_in.c \
  ft_path_finding.c \
  ft_run_hans.c \
  lem_in.c \
  ft_func.c

OBJ=$(SRC:.c=.o)

$(NAME):
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(OBJ) -o $(NAME) libft.a libftprintf.a

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
