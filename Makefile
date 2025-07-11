CC = cc
FLAGS = -Wall -Wextra -Werror -O3
ENTRY = ./cub3d.c
SRCS =  ./srcs/init.c \
./srcs/map.c \
./srcs/hooks.c \
./srcs/raycast.c \
./srcs/intersec1.c \
./srcs/intersec2.c \
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
./srcs/moves.c \
./srcs/raycast_utils.c
OBJS = $(SRCS:%.c=%.o)
INCLUDE = .
MLX_MACOS = -framework Cocoa -framework OpenGL -framework IOKit
MLX_INCLUDE = ./MLX42/include/MLX42.h
MLX42_DIR = ./MLX42
GLFW = -lglfw -L/Users/nhayoun/.brew/opt/glfw/lib/
GLFW_LINUX = -ldl -lglfw -pthread -lm
MLX_AR = ./MLX42/build/libmlx42.a
LIBR = libr.a
NAME = cub3D

all: linux

%.o: %.c $(INCLUDE)
	@echo "Compiling $<..."
	@$(CC) $(FLAGS) -I$(INCLUDE) -I$(MLX_INCLUDE) -c $< -o $@

$(LIBR):
	make -C libr

$(MLX42_DIR):
	@echo "Cloning MLX42..."
	@git clone https://github.com/codam-coding-college/MLX42.git > /dev/null 2>&1
	@echo "MLX42 has been successfully cloned."

$(MLX_AR): $(MLX42_DIR)
	@echo "Building MLX42..."
	@git submodule update --init --recursive
	@cd MLX42 && cmake -B build && cmake --build build -j4 > /dev/null 2>&1
	@echo "MLX42 has been successfully built." > /dev/null 2>&1

$(NAME): $(ENTRY) $(SRCS) $(MLX_AR) $(OBJS) $(INCLUDE)
	@$(CC) $(FLAGS) -lm $(OBJS) -I$(INCLUDE) -I$(MLX_INCLUDE) $(ENTRY) $(MLX_AR)  $(LIBR) $(GLFW) -o $(NAME)
	@echo "Program Compiled successfully."

linux: $(LIBR) $(MLX_AR) $(OBJS)
	@echo "Building for Linux..."
	@$(CC) $(FLAGS) -lm $(OBJS) -I$(INCLUDE) -I$(MLX_INCLUDE) $(ENTRY) $(MLX_AR) $(LIBR) $(GLFW_LINUX) -o $(NAME)
	@echo "Linux build completed."

macos: $(LIBR) $(MLX_AR) $(OBJS)
	@echo "Building for macOS..."
	@$(CC) $(FLAGS) -lm $(OBJS) -I$(INCLUDE) -I$(MLX_INCLUDE) $(ENTRY) $(MLX_AR) $(LIBR) $(MLX_MACOS) $(GLFW) -o $(NAME)
	@echo "macOS build completed."

clean:
	make clean -C libr
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(LIBR) $(NAME)

re: fclean all
