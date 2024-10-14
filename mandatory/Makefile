cc = CC
FLAGS = -Wall -Wextra -Werror -O3 
ENTRY = cub3d.c
SRCS =	./srcs/init.c \
./srcs/map.c \
./srcs/hooks.c \
./srcs/raycast.c \
./srcs/intersec.c \
./srcs/texture.c \
./srcs/utils.c \
./srcs/utilities.c \
./srcs/utilities2.c \
./srcs/utilities3.c \
./srcs/utilities4.c \
./srcs/map_test.c \
./srcs/get_next_line.c \
./srcs/get_next_line_utils.c \
./srcs/ft_split.c \
./srcs/map_pretests.c \
./srcs/map_textures_tests.c \
./srcs/map_textures_tests2.c \
./srcs/map_parsing_tests.c \
./srcs/map_parsing_tests2.c \
./srcs/moves.c
INCLUDE = .
OBJS = $(SRCS:%.c=%.o)
MLX_MACOS = -framework Cocoa -framework OpenGL -framework IOKit
MLX_INCLUDE = ../MLX42/include/MLX42.h
MLX_AR = ../MLX42/build/libmlx42.a
GLFW = -lglfw -L/Users/ael-maaz/.brew/opt/glfw/lib/
GLFW_LINUX = -ldl -lglfw -pthread -lm
LIBR = ../libr.a
NAME = ../cub3D

%.o: %.c $(INCLUDE)
	@echo "Compiling $<..."
	@$(CC) $(FLAGS) -I$(INCLUDE) -I$(MLX_INCLUDE) -c $< -o $@

$(NAME): $(MLX_AR) $(OBJS) $(INCLUDE)
	@$(CC) $(FLAGS) -lm $(OBJS) -I$(INCLUDE) $(ENTRY) $(MLX_AR)  $(LIBR) $(GLFW) -o $(NAME)
	@echo "Program Compiled successfully."

clean:
	rm -rf $(OBJS)
