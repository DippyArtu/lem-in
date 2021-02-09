cmake_minimum_required(VERSION 3.17)
project(lem_in)

set(CMAKE_C_STANDARD 99)

include_directories(includes)
include_directories(shaders)
include_directories(libft/includes)
include_directories(libhash/includes)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

find_library(GLFW_LIB glfw HINTS /usr/local/lib)
find_library(GLEW_LIB glew HINTS /usr/local/lib)

add_executable(lem_in
        libft/includes/get_next_line.h
        libft/includes/libft.h
        libft/srcs/ft_arrnew.c
        libft/srcs/ft_atoi.c
        libft/srcs/ft_bzero.c
        libft/srcs/ft_isalnum.c
        libft/srcs/ft_isalpha.c
        libft/srcs/ft_isascii.c
        libft/srcs/ft_isdigit.c
        libft/srcs/ft_isprint.c
        libft/srcs/ft_itoa.c
        libft/srcs/ft_lstadd.c
        libft/srcs/ft_lstdel.c
        libft/srcs/ft_lstdelone.c
        libft/srcs/ft_lstiter.c
        libft/srcs/ft_lstmap.c
        libft/srcs/ft_lstnew.c
        libft/srcs/ft_lstnull.c
        libft/srcs/ft_memalloc.c
        libft/srcs/ft_memccpy.c
        libft/srcs/ft_memchr.c
        libft/srcs/ft_memcmp.c
        libft/srcs/ft_memcpy.c
        libft/srcs/ft_memdel.c
        libft/srcs/ft_memmove.c
        libft/srcs/ft_memset.c
        libft/srcs/ft_putchar.c
        libft/srcs/ft_putchar_fd.c
        libft/srcs/ft_putendl.c
        libft/srcs/ft_putendl_fd.c
        libft/srcs/ft_putnbr.c
        libft/srcs/ft_putnbr_fd.c
        libft/srcs/ft_putstr.c
        libft/srcs/ft_putstr_fd.c
        libft/srcs/ft_skipnchars.c
        libft/srcs/ft_strcat.c
        libft/srcs/ft_strchr.c
        libft/srcs/ft_strclr.c
        libft/srcs/ft_strcmp.c
        libft/srcs/ft_strcpy.c
        libft/srcs/ft_strdel.c
        libft/srcs/ft_strdup.c
        libft/srcs/ft_strdup_till_char.c
        libft/srcs/ft_strequ.c
        libft/srcs/ft_striter.c
        libft/srcs/ft_striteri.c
        libft/srcs/ft_strjoin.c
        libft/srcs/ft_strjoinf.c
        libft/srcs/ft_strlcat.c
        libft/srcs/ft_strlen.c
        libft/srcs/ft_strmap.c
        libft/srcs/ft_strmapi.c
        libft/srcs/ft_strncat.c
        libft/srcs/ft_strncmp.c
        libft/srcs/ft_strncpy.c
        libft/srcs/ft_strnequ.c
        libft/srcs/ft_strnew.c
        libft/srcs/ft_strnstr.c
        libft/srcs/ft_strrchr.c
        libft/srcs/ft_strsplit.c
        libft/srcs/ft_strsplit_arrc.c
        libft/srcs/ft_strstr.c
        libft/srcs/ft_strstr_valid.c
        libft/srcs/ft_strsub.c
        libft/srcs/ft_strsubptr.c
        libft/srcs/ft_strtrim.c
        libft/srcs/ft_swap.c
        libft/srcs/ft_tolower.c
        libft/srcs/ft_toupper.c
        libft/srcs/ft_wordcounter.c
        libft/srcs/get_next_line.c
        libft/Makefile

        libhash/includes/hash_table.h
        libhash/includes/prime.h
        libhash/srcs/hash_table.c
        libhash/srcs/prime.c
        libhash/Makefile

        shaders/vertex.shader
        shaders/geometry.shader
        shaders/fragment.shader

        includes/lem-in.h
        includes/map_structs.h
        includes/errors.h
        includes/gl_includes.h
        includes/stb_image.h

        srcs/main.c
        srcs/parse_map.c
        srcs/init.c
        srcs/clean_up.c
        srcs/errors.c
        srcs/room_utils.c
        srcs/parse_rooms.c
        srcs/parse_links.c
        srcs/links_utils.c
        srcs/gl_utils.c
        srcs/gl_build.c
        srcs/gl_buffers.c
        srcs/gl_points.c
        srcs/gl_draw.c)

target_link_libraries(lem_in ${GLFW_LIB} ${GLEW_LIB})