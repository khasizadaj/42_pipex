/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:34:41 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/02/17 23:47:53 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "../src/libft/libft.h"

# define PATH_ERR 11
# define PATH_ERR_MSG "PATH doesn't exist"

# define MEMO_ERR 12
# define MEMO_ERR_MSG "Memory allocation failed"

# define USAGE_ERR 13
# define USAGE_ERR_MSG "Usage: ./pipex file1 cmd1 cmd2 file2"

# define ACCESS_ERR 14
# define ACCESS_ERR_MSG "Access error\n"

# define COMMAND_ERR 15
# define COMMAND_ERR_MSG "Command error\n"

# define UNKNOWN_ERR 10
# define UNKNOWN_ERR_MSG "Unknown error\n"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_data
{
    char    **dirs;
    int     in_fd;
    int     out_fd;
    int     exit_code;
}   t_data;

void	exit_gracefully(t_data *data, int reason);
void	init_data(t_data *data);
void    ft_putchar(char c);

#endif
