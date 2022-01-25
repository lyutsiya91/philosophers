NAME 	= philo_bonus
HEADER  = philo_bonus.h
SRC 	= actions_bonus.c \
		control_bonus.c \
		init_bonus.c \
		philo_bonus.c \
		timing_bonus.c \
		utils_bonus.c \

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