/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:08:27 by codespace         #+#    #+#             */
/*   Updated: 2024/02/04 18:46:27 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

void	flush_buffer(t_fd *file)
{
	size_t			i;
	size_t			j;

	i = 0;
	while (file->buffer[i] != '\n' && file->buffer[i] != '\0')
		i++;
	if (file->buffer[i] == '\n')
		i++;
	j = -1;
	while (file->buffer[i] != '\0' && i < BUFFER_SIZE)
		file->buffer[++j] = file->buffer[i++];
	while (++j < BUFFER_SIZE)
		file->buffer[j] = '\0';
}

char	*transfer(char *line, t_fd *f)
{
	char	*temp;

	temp = line;
	line = ft_strjoin_until(temp, f->buffer, '\n');
	if (!line)
		return (free(temp), NULL);
	free(temp);
	flush_buffer(f);
	return (line);
}

char	*process(t_fd *f)
{
	char	*line;

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (ft_strlen_until(f->buffer, '\0') > 0)
	{
		line = transfer(line, f);
		if (!line)
			return (NULL);
	}
	while (!chr_in('\n', line))
	{
		f->rd = read(f->fd, f->buffer, BUFFER_SIZE);
		if (f->rd == 0 && ft_strlen_until(line, '\0') > 0)
			return (line);
		else if (f->rd <= 0)
			return (free(line), NULL);
		line = transfer(line, f);
		if (!line)
			return (NULL);
	}
	return (line);
}

/*

Static file used here is treated as list of files
and it's open for extension. However, there can be
one file at a time.

*/

int	get_next_line(int fd, char **line, bool include_newline)
{
	static t_fd	*file = NULL;
	char		*line_no_newline;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (ft_clear(&file), -1);
	if (!file)
	{
		file = ft_newfd(fd);
		if (!file)
			return (-1);
	}
	*line = process(file);
	if (!*line && file->rd == 0)
		return (ft_clear(&file), 0);
	else if (!*line)
		return (ft_clear(&file), -1);
	if (!include_newline && chr_in('\n', *line) == 1)
	{
		line_no_newline = ft_substr(*line, 0, ft_strlen(*line) - 1);
		if (!line_no_newline)
			return (ft_clear(&file), -1);
		free(*line);
		*line = line_no_newline;
	}
	return (ft_strlen(*line));
}
