# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 14:13:14 by bschwitz          #+#    #+#              #
#    Updated: 2023/01/09 18:28:29 by bschwitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isprint.c ft_memchr.c ft_isdigit.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_malloc.c ft_memzero.c ft_free.c ft_realloc.c \
				ft_strisspace.c ft_strcpy.c ft_strncat.c ft_strcat.c ft_putstr.c ft_isspace.c ft_strtrim_all.c ft_free_arr.c ft_split2.c ft_strisnumber.c ft_strcmp.c free_arr.c \
 				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lst_get_data_last_node.c ft_lst_sort_str.c ft_lstdel.c ft_lstdup.c 

OBJS		= ${SRCS:.c=.o}

OBJSBONUS	= ${BONUS:.c=.o}

NAME		= libft.a

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Werror -Wextra

all:		${NAME}

${NAME}:	${OBJS}
			ar cr ${NAME} ${OBJS}

bonus:		${OBJS} ${OBJSBONUS}
			ar r ${NAME} ${OBJSBONUS}

clean:
			${RM} ${OBJS} ${OBJSBONUS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
