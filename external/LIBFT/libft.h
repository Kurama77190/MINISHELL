/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 04:09:01 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/21 05:40:51 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char				**ft_split_envp(char const *s, char c);

int					ft_strcmp(const char *s1, const char *s2);

bool				ft_isspace(char c);

bool				ft_is_operator(char c);

bool				is_redir(char c);

char				**split_token(char const *s);

void				free_split(char **strs);

void				ft_free(void **ptr);

int					ft_atoi(const char *str);

void				ft_bzero(void *s, size_t n);

void				*ft_calloc(size_t count, size_t size);

int					ft_isalnum(int c);

int					ft_isalpha(int c);

int					ft_isascii(int c);

int					ft_isdigit(int c);

int					ft_isprint(int c);

char				*ft_itoa(int n);

void				*ft_memchr(const void *s, int c, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_memcpy(void *dest, const void *src, size_t n);

void				*ft_memmove(void *dst, const void *src, size_t len);

void				*ft_memset(void *b, int c, size_t len);

void				ft_putchar_fd(char c, int fd);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr_fd(int n, int fd);

void				ft_putstr_fd(char *s, int fd);

char				**ft_split(char const *s, char c);

// Recherche la première occurrence d'un caractère dans une chaîne.
char				*ft_strchr(const char *s, int c);

char				*ft_strdup(const char *s1);

char				*ft_strjoin(char const *s1, char const *s2);

size_t				ft_strlcat(char *dst, const char *src, size_t size);

size_t				ft_strlcpy(char *dst, const char *src, size_t size);

size_t				ft_strlen(const char *str);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strncmp(const char *s1, const char *s2, size_t n);

char				*ft_strnstr(const char *s1, const char *s2, size_t n);

char				*ft_strrchr(const char *s, int c);

char				*ft_strtrim(char const *s1, char const *set);

char				*ft_substr(char const *s, unsigned int start, size_t len);

int					ft_tolower(int c);

int					ft_toupper(int c);

t_list				*ft_lstnew(void *content);

int					ft_lstsize(t_list *lst);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstadd_front(t_list **alst, t_list *new);

void				ft_lstadd_back(t_list **alst, t_list *new);

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstclear(t_list **lst, void (*del)(void *));

void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif