CC = cc
FLAGS = -Wall -Wextra -Werror
SRCS = ./libft/ft_isascii.c \
	./libft/ft_isalpha.c \
	./libft/ft_isdigit.c \
	./libft/ft_isprint.c \
	./libft/ft_isalnum.c \
	./libft/ft_memset.c \
	./libft/ft_strlcpy.c \
	./libft/ft_strlcat.c \
	./libft/ft_toupper.c \
	./libft/ft_tolower.c \
	./libft/ft_strchr.c \
	./libft/ft_strrchr.c \
	./libft/ft_strncmp.c \
	./libft/ft_memchr.c \
	./libft/ft_memcmp.c \
	./libft/ft_strnstr.c \
	./libft/ft_itoa.c \
	./libft/ft_calloc.c \
	./libft/ft_strjoin.c \
	./libft/ft_strtrim.c \
	./libft/ft_striteri.c \
	./libft/ft_strmapi.c \
	./libft/ft_putchar_fd.c \
	./libft/ft_putstr_fd.c \
	./libft/ft_putnbr_fd.c \
	./libft/ft_putendl_fd.c \
	./libft/ft_lstnew.c \
	./libft/ft_lstadd_front.c \
	./libft/ft_lstsize.c \
	./libft/ft_lstlast.c \
	./libft/ft_lstadd_back.c \
	./libft/ft_lstdelone.c \
	./libft/ft_lstclear.c \
	./libft/ft_lstiter.c \
	./libft/ft_lstmap.c \
	./libft/utilities.c
OBJS = $(SRCS:.c=.o)
NAME = ../libr.a
INCLUDE = .

all: $(NAME)

$(NAME): $(INCLUDE) $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME)

re: fclean all
