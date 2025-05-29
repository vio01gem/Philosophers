# NAME = philo
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -pthread
# SRC = main.c philo_utils.c philo_parse.c philo_clean.c philo_init.c philo_cycle.c philo_monitor.c philo_forks.c
# OBJ = $(SRC:.c=.o)

# %.o: %.c philo.h
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# all: $(NAME)

# clean:
# 	rm -f $(OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main.c philo_utils.c philo_parse.c philo_clean.c philo_init.c philo_cycle.c \
	  philo_monitor.c philo_forks.c
OBJ_DIR = .o_files
# OBJ = .o_files/main.o .o_files/philo_utils.o .o_files/philo_parse.o .o_files/philo_clean.o \
#       .o_files/philo_init.o .o_files/philo_cycle.o .o_files/philo_monitor.o .o_files/philo_forks.o
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

$(OBJ_DIR)/%.o: %.c philo.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
