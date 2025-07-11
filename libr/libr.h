/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:06:07 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/29 19:03:08 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBR_H

# define LIBR_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isascii(int c);

int					ft_isprint(int c);

int					ft_isalnum(int c);

int					ft_isalpha(int c);

void				*ft_memset(void *b, int c, size_t len);

size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);

int					ft_toupper(int c);

int					ft_tolower(int c);

char				*ft_strchr(const char *s, int c);

int					ft_strncmp(const char *s1, const char *s2, size_t n);

char				*ft_strrchr(const char *s, int c);

void				*ft_memchr(const void *s, int c, size_t n);

char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

void				*ft_calloc(size_t count, size_t size);

char				*ft_strtrim(char const *s1, char const *set);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void				ft_putchar_fd(char c, int fd);

void				ft_putstr_fd(char *s, int fd);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void *content);

void				ft_lstadd_front(t_list **lst, t_list *new);

int					ft_lstsize(t_list *lst);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstclear(t_list **lst, void (*del)(void *));

void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_strlen(const char *s);
void				ft_bzero(void *s, int n);
void				*ft_memcpy(void *dst, const void *src, int n);
void				*ft_memmove(void *dst, const void *src, int len);

char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, int start, int len);
int					ft_fcmp(const char *s1, const char *s2);
int					ft_isdigit(int c);
int					ft_atoi(char *s, int *error, int i, int sign);
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);

#endif
