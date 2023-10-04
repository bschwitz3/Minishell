/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:21:22 by bschwitz          #+#    #+#             */
/*   Updated: 2023/01/10 13:23:11 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_malloc(size_t size);
void	*ft_memzero(void *dst, size_t n);
void	*ft_realloc(void *mem, size_t old_size, size_t new_size);
void	ft_free(void *mem);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	*ft_lst_get_data_last_node(t_list *lst);
void	ft_lst_sort_str(t_list **lst, int (*op)(char *, char *));
void	ft_lstdel_int(void *data);
void	ft_lstdel_first(t_list **lst, void (*del)(void*));
void	ft_lstdel_last(t_list *lst, void (*del)(void*));
void	ft_lstdel_middle(t_list **lst, int node_nbr, void (*del)(void*));
void	ft_lstclear_if(t_list **lst, int (*cmp)(void *), void (*del)(void *));
t_list	*ft_lstdup(t_list *lst);

int		ft_strisspace(char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, char *src, size_t n);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
char	*ft_strtrim_all(const char *s1, const char *set);
char	*ft_strcat(char *dest, char *src);
int		ft_putstr(char *str);
int		ft_isspace(char c);
void	free_arr(void **ptr);
char	**ft_split2(char *str, char *charset);
int		ft_strisnumber(char *s);
int		ft_strcmp(char *s1, char *s2);
void	free_arr(void **ptr);

t_list	*ft_lstbeforelast(t_list *lst);
void	ft_lstadd_before_back(t_list **alst, t_list *new);

#endif
