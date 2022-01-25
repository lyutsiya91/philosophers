NAME 	= philo
HEADER  = philo.h
SRC 	= actions.c \
		control.c \
		init.c \
		philo.c \
		timing.c \
		utils.c \

OBJ 	= $(patsubst %.c, %.o, $(SRC))
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
PTFLAG  = -pthread
RM		= rm -rf

%o : %c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(PTFLAG) $(OBJ) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re