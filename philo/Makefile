NAME = philo 
CC = cc
CFLAGS = -Wall -Werror -Wextra
COMPILE_FLAG = -c
HEADER = philo.h

SRC = main.c parse.c eater_routine.c monitor_routine.c pre_threads.c uti.c clean.c
OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(COMPILE_FLAG) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)
re : fclean all

.PHONY: all clean fclean re