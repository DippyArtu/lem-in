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
		links_utils.c \
		gl_utils.c \
		gl_build.c \
		graphics.c \
		gl_buffers.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
OBJ_DIR = ./obj/
OBJ = $(SRC:.c=.o)

INCS = $(addprefix $(INC_DIR), $(INC))
INC_DIR = ./includes/
INC = 	lem-in.h \
		map_structs.h \
		errors.h \
		gl_includes.h \
		stb_image.h

LIB_OBJS = $(addprefix $(LIB_OBJ_DIR), $(LIB_OBJ))
LIB_OBJ = *.o
LIB_OBJ_DIR = ./libft/obj/
LIB_SRC_DIR = ./libft/srcs/
LIB_INCS = $(addprefix $(LIB_INC_DIR), $(LIB_INC))
LIB_INC = libft.h get_next_line.h
LIB_INC_DIR = ./libft/includes/

HASH_OBJS = $(addprefix $(HASH_OBJ_DIR), $(HASH_OBJ))
HASH_OBJ = *.o
HASH_OBJ_DIR = ./libhash/obj/
HASH_SRC_DIR = ./libhash/srcs/
HASH_INCS = $(addprefix $(HASH_INC_DIR), $(HASH_INC))
HASH_INC_DIR = ./libhash/includes/
HASH_INC = hash_table.h prime.h

FLAGS = -Werror -Wextra -Wall -I$(INC_DIR) -I$(LIB_INC_DIR) -I$(HASH_INC_DIR)
GL_LIBS = -framework OpenGL -I/usr/local/include -lGLEW -lglfw

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIB_OBJS) $(HASH_OBJS) $(OBJS)
		clang $(OBJS) ./libft/libft.a ./libhash/libhash.a -o $(NAME) $(GL_LIBS)

$(OBJ_DIR):
		mkdir -p $@
		@mkdir -p $(LIB_OBJ_DIR)
		@mkdir -p $(HASH_OBJ_DIR)

$(LIB_OBJ_DIR)%.o: $(LIB_SRC_DIR)%.c $(LIB_INCS)
		@make -C libft

$(HASH_OBJ_DIR)%.o: $(HASH_SRC_DIR)%.c $(HASH_INCS)
		@make -C libhash

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
		clang $(FLAGS) -o $@ -c $<

clean:
		@make clean -C libft
		@make clean -C libhash
		@rm -f $(OBJS)
		@rm -rf $(OBJ_DIR)

fclean: clean
		@make fclean -C libft
		@make fclean -C libhash
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re