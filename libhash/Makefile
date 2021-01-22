#########################################
##                                     ##
##      LibHash project                ##
##                                     ##
##      Created by Artur Makhnach      ##
##      github.com/DippyArtu           ##
##      artum.me                       ##
##                                     ##
#########################################

NAME = libhash.a

SRC_DIR = ./srcs/
SRC =	hash_table.c \
		prime.c

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

INC = hash_table.h \
		prime.h
INC_DIR = ./includes/
INCS = $(addprefix $(INC_DIR), $(INC))

FLAGS = -g -Wall -Werror -Wextra -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
		@ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
		clang $(FLAGS) -o $@ -c $<

clean:
		@rm -f $(OBJS)
		@rm -rf $(OBJ_DIR)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
