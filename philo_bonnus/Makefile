NAME = philo_bonus
CC = cc
# -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror -g3

SRCS_BNS = main.c\
	functions_utils.c\
	philosophers_life.c\
	time_managment.c\
	clean_manager.c\
	create_philo_and_manager.c

OBJS_BNS = $(SRCS_BNS:.c=.o)

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

$(NAME): $(OBJS_BNS)
	$(CC) $(CFLAGS) $(OBJS_BNS) -o ${NAME}

clean:
	rm -rf ${OBJS_BNS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

