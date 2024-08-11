cc = CC
FLAGS = -Wall -Wextra -Werror -O3
ENTRY = cub3d.c
SRCS =	./srcs/init.c
INCLUDE = .
OBJS = $(SRCS:%.c=%.o)
MLX_MACOS = -framework Cocoa -framework OpenGL -framework IOKit
MLX_INCLUDE = ../MLX42/include/MLX42.h
MLX_AR = ../MLX42/build/libmlx42.a
GLFW = -lglfw -L/Users/nhayoun/.brew/opt/glfw/lib/
GLFW_LINUX = -ldl -lglfw -pthread -lm
NAME = ../cub3D

%.o: %.c $(INCLUDE)
	@echo "Compiling $<..."
	@$(CC) $(FLAGS) -I$(INCLUDE) -I$(MLX_INCLUDE) -c $< -o $@

$(NAME): $(MLX_AR) $(OBJS) $(INCLUDE)
	@$(CC) $(FLAGS) $(OBJS) -I$(INCLUDE) $(ENTRY) $(MLX_AR) $(GLFW_LINUX) -o $(NAME)
	@echo "Program Compiled successfully."

clean:
	rm -rf $(OBJS)