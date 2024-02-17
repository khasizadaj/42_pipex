/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:29:57 by codespace         #+#    #+#             */
/*   Updated: 2024/01/28 01:33:30 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_fd
{
	int			fd;
	char		*buffer;
	struct s_fd	*next;
	int			rd;
}	t_fd;

int		get_next_line(int fd, char **line, bool include_newline);
t_fd	*ft_newfd(int fd);
void	ft_clear(t_fd **to_be_removed);
int		chr_in(char c, char const *str);
char	*ft_strjoin_until(const char *s1, const char *s2, char until);
size_t	ft_strlen_until(const char *s, char until);
size_t	ft_strlen(const char *s);

#endif