NAME = philo_bonus
CFLAGS = -Wall -Werror -Wextra
CC = cc
COMPILE_FLAG = -c
SRC = main.c \
      init.c \
      spawn_n_eater_transform.c \
      eater_thread_routine.c \
      eater_monitor_routine.c \
      parse1_check_legitimacy.c \
      parse2_load.c \
      clean_helper1.c \
      clean_helper2.c \
      uti.c
OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

%.o : %.c philo_bonus.h
	$(CC) $(CFLAGS) $(COMPILE_FLAG) $< -o $@ 

clean:
	rm -f $(OBJ)
fclean:clean
	rm -f $(NAME)
re: fclean all