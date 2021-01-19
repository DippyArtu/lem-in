#########################################
##                                     ##
##      Lem-in project                 ##
##                                     ##
##      Created by Artur Makhnach      ##
##      github.com/DippyArtu           ##
##      artum.me                       ##
##                                     ##
#########################################

NAME = lem-in

SRC_DIR = ./srcs/
SRC = 	main.c \
		parse_map.c \
		init.c \
		clean_up.c \
		errors.c \
		room_utils.c \
		parse_rooms.c \
		parse_links.c \
		links_utils.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
OBJ_DIR = ./obj/
OBJ = $(SRC:.c=.o)

INCS = $(addprefix $(INC_DIR), $(INC))
INC_DIR = ./includes/
INC = 	lem-in.h \
		map_structs.h \
		errors.h

LIB_OBJS = $(addprefix $(LIB_OBJ_DIR), $(LIB_OBJ))
LIB_OBJ = *.o
LIB_OBJ_DIR = ./libft/obj/

LIB_SRC_DIR = ./libft/srcs/

LIB_INCS = $(addprefix $(LIB_INC_DIR), $(LIB_INC))
LIB_INC = libft.h get_next_line.h
LIB_INC_DIR = ./libft/includes/

FLAGS = -Werror -Wextra -Wall -I$(INC_DIR) -I$(LIB_INC_DIR)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIB_OBJS) $(OBJS)
		clang $(OBJS) ./libft/libft.a -o $(NAME)

$(OBJ_DIR):
		mkdir -p $@
		@mkdir -p $(LIB_OBJ_DIR)

$(LIB_OBJ_DIR)%.o: $(LIB_SRC_DIR)%.c $(LIB_INCS)
		@make -C libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
		clang $(FLAGS) -o $@ -c $<

clean:
		@make clean -C libft
		@rm -f $(OBJS)
		@rm -rf $(OBJ_DIR)

fclean: clean
		@make fclean -C libft
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re