/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:34:41 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/07 13:45:28 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "../src/libft/libft.h"

# define EXEC_ERR 6
# define EXEC_ERR_MSG "Execution failed\n"

# define PATH_ERR 11
# define PATH_ERR_MSG "PATH doesn't exist\n"

# define MEMO_ERR 12
# define MEMO_ERR_MSG "Memory allocation failed\n"

# define USAGE_ERR 13
# define USAGE_ERR_MSG "Usage: ./pipex file1 cmd1 cmd2 file2\n"

# define ACCESS_ERR 14
# define ACCESS_ERR_MSG "File went on a little vacation.\n"

# define COMMAND_ERR 15
# define COMMAND_ERR_MSG "Command doesn't exist. Learn bash, pls!\n"

# define UNKNOWN_ERR 10
# define UNKNOWN_ERR_MSG "Unknown error\n"

# define PIPE_ERR 16
# define PIPE_ERR_MSG "Pipe couldn't be created\n"

# define FORK_ERR 17
# define FORK_ERR_MSG "Fork couldn't be created\n"

typedef struct s_command
{
    char    *path;
    char    **args;
}   t_command;

typedef struct s_data
{
    char        **dirs;
    int         cmd_count;
    t_command   **cmds;
    int         **pipes;
    char        **envp;
    int         in_fd;
    int         out_fd;
    int         exit_code;
}   t_data;

void	    exit_gracefully(t_data *data, int reason);
void        free_commmands(t_command **cmds);
void        free_dirs(t_data *data);
void        free_pipes(t_data *data);
void        close_pipes(t_data *data, int child_proc_id, bool close_all);
void	    init_commands(t_data *data);
void	    init_data(t_data *data, char **envp);
void        init_pipes(t_data *data);
t_command	*get_command(t_data *data, char *raw_command);


#endif
