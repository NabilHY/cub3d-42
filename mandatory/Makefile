cc = CC
FLAGS = -Wall -Wextra -Werror -O3
ENTRY = cub3d.c
SRCS =	./srcs/init.c \
./srcs/map.c \
./srcs/hooks.c \
./srcs/raycast.c
INCLUDE = .
OBJS = $(SRCS:%.c=%.o)
MLX_MACOS = -framework Cocoa -framework OpenGL -framework IOKit
MLX_INCLUDE = ../MLX42/include/MLX42.h
MLX_AR = ../MLX42/build/libmlx42.a
GLFW = -lglfw -L/Users/nhayoun/.brew/opt/glfw/lib/
GLFW_LINUX = -ldl -lglfw -pthread -lm
LIBR = ../libr.a
NAME = ../cub3D

%.o: %.c $(INCLUDE)
	@echo "Compiling $<..."
	@$(CC) $(FLAGS) -I$(INCLUDE) -I$(MLX_INCLUDE) -c $< -o $@

$(NAME): $(MLX_AR) $(OBJS) $(INCLUDE)
	@$(CC) $(FLAGS) -fsanitize=address $(OBJS) -I$(INCLUDE) $(ENTRY) $(MLX_MACOS) $(MLX_AR) $(LIBR) $(GLFW) -o $(NAME)
	@echo "Program Compiled successfully."

clean:
	rm -rf $(OBJS)