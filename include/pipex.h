/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:34:41 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/16 19:43:38 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "../src/libft/libft.h"

# define EXEC_ERR 1
# define EXEC_ERR_MSG "Execution failed\n"

# define PATH_ERR 1
# define PATH_ERR_MSG "PATH doesn't exist\n"

# define MEMO_ERR 1
# define MEMO_ERR_MSG "Memory allocation failed\n"

# define USAGE_ERR 1
# define USAGE_ERR_MSG "Usage: ./pipex file1 cmd1 cmd2 file2\n"

# define FILE_ERR_NO_FILE 1
# define FILE_ERR_NO_PERM 2

# define ACCESS_ERR 1
# define ACCESS_ERR_MSG "File is not accesible.\n"

# define COMMAND_ERR 127
# define COMMAND_ERR_MSG "Command doesn't exist. Learn bash, pls!\n"

# define UNKNOWN_ERR 1
# define UNKNOWN_ERR_MSG "Unknown error\n"

# define PIPE_ERR 1
# define PIPE_ERR_MSG "Pipe couldn't be created\n"

# define FORK_ERR 1
# define FORK_ERR_MSG "Fork couldn't be created\n"

# define DUP2_IN_ERR 1
# define DUP2_IN_ERR_MSG "dup2 failed for read end.\n"

# define DUP2_OUT_ERR 1
# define DUP2_OUT_ERR_MSG "dup2 failed for write end.\n"

typedef struct s_command
{
	char	*path;
	char	**args;
}	t_command;

typedef struct s_data
{
	char		**dirs;
	int			cmd_count;
	t_command	**cmds;
	int			**pipes;
	int			*pids;
	char		**envp;
	int			in_fd;
	int			out_fd;
	int			exit_code;
}	t_data;

void		parse_input(t_data *data, int argc, char **argv);
void		exit_gracefully(t_data *data, int reason, char *msg,
				bool with_message);
void		print_file_error(int reason, char *filename);
void		free_commmands(t_command **cmds);
void		free_dirs(t_data *data);
void		free_pipes(t_data *data);
void		close_pipes(t_data *data);
void		init_commands(t_data *data);
void		run_commands(t_data *data);
void		wait_for_processes(t_data *data);
void		init_pids(t_data *data);
void		init_data(t_data *data, char **envp);
void		init_pipes(t_data *data);
void		handle_read_redirection(t_data *data, int i);
void		handle_write_redirection(t_data *data, int i);
void		set_arg_as_path(t_data *data, t_command *command);
t_command	*get_command(t_data *data, char *raw_command);

#endif
