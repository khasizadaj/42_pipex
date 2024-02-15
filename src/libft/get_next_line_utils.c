/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:29:54 by codespace         #+#    #+#             */
/*   Updated: 2024/01/28 00:03:55 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd	*ft_newfd(int fd)
{
	t_fd	*node;
	int		i;

	node = malloc(sizeof(t_fd));
	if (!node)
		return (NULL);
	node->buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!node->buffer)
		return (free(node), NULL);
	i = -1;
	while (++i < BUFFER_SIZE)
		(node->buffer)[i] = (unsigned char) '\0';
	node->buffer[BUFFER_SIZE] = '\0';
	node->rd = 0;
	node->fd = fd;
	node->next = NULL;
	return (node);
}

void	ft_clear(t_fd **to_be_removed)
{
	if (!*to_be_removed)
		return ;
	free((*to_be_removed)->buffer);
	free(*to_be_removed);
	*to_be_removed = NULL;
}

char	*ft_strjoin_until(const char *s1, const char *s2, char until)
{
	int		len_1;
	int		len_2;
	char	*joined;
	int		i;

	len_1 = ft_strlen_until(s1, '\0');
	len_2 = ft_strlen_until(s2, '\n');
	joined = malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (joined == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
	{
		joined[i] = s1[i];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		joined[len_1 + i] = s2[i];
		if (s2[i++] == until)
			break ;
	}
	joined[len_1 + i] = '\0';
	return (joined);
}

size_t	ft_strlen_until(const char *s, char until)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i++] == until)
			break ;
	}
	return (i);
}

int	chr_in(char c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
