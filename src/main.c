/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:30:33 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/07 19:44:07 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*extract_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/*
	Function validates the inputs provided by the user. Like bash,
	it only informs the user about issues.
	
	Having errors doesn't stop the program from running except
	provided argument count is less than 4 (i.e. 5 with program name).
*/
void	validate_input(t_data *data)
{
	int	i;


	i = -1;
	while (++i < data->cmd_count)
	{
		printf("path: %s\n", data->cmds[i]->path);
		if (data->cmds[i]->path && access(data->cmds[i]->path, X_OK) == -1)
			ft_putstr_fd(COMMAND_ERR_MSG, STDERR_FILENO);
	}
}

void	parse_input(t_data *data, int argc, char **argv)
{
	int			fd;
	int			i;
	t_command	*cmd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		ft_putstr_fd(ACCESS_ERR_MSG, STDERR_FILENO);
	data->in_fd = fd;
	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit_gracefully(data, ACCESS_ERR);
	data->out_fd = fd;
	data->cmd_count = argc - 3;
	init_commands(data);
	init_pids(data);
	i = 2;
	while (i < argc - 1)
	{
		cmd = get_command(data, argv[i]);
		if (!cmd)
			exit_gracefully(data, MEMO_ERR);
		data->cmds[i - 2] = cmd;
		i++;
	}
}

void	handle_write_redirection(t_data *data, int i)
{
	if (i == data->cmd_count - 1)
	{
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
		{
			close_pipes(data);
			exit_gracefully(data, 103);
		}
	}
	else
	{
		if (dup2(data->pipes[i + 1][1], STDOUT_FILENO) == -1)
		{
			close_pipes(data);
			exit_gracefully(data, 102);
		}
	}
}

void	handle_read_redirection(t_data *data, int i)
{
	if (i == 0)
	{
		if (data->in_fd == -1)
		{
			close_pipes(data);
			exit_gracefully(data, 0);
		}
		if (dup2(data->in_fd, STDIN_FILENO) == -1)
		{
			close_pipes(data);
			exit_gracefully(data, 110);
		}
	}	
	else
	{
		if (dup2(data->pipes[i][0], STDIN_FILENO) == -1)
		{
			close_pipes(data);
			exit_gracefully(data, 101);
		}
	}
}

void	run_commands(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			exit_gracefully(data, FORK_ERR);
		if (data->pids[i] == 0)
		{
			handle_read_redirection(data, i);
			handle_write_redirection(data, i);
			close_pipes(data);
			if (!data->cmds[i]->path)
				exit_gracefully(data, 192);
			if (execve(data->cmds[i]->path, data->cmds[i]->args, data->envp) == -1)
				exit_gracefully(data, EXEC_ERR);
		}
	}
	i = -1;
	close_pipes(data);
	while (++i < data->cmd_count)
		waitpid(data->pids[i], NULL, 0);
}

void	run(t_data *data)
{
	init_pipes(data);
	run_commands(data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	t_data	data;

	init_data(&data, envp);
	if (argc < 5)
		exit_gracefully(&data, USAGE_ERR);
	path = extract_path(envp);
	if (!path)
		exit_gracefully(&data, PATH_ERR);
	data.dirs = ft_split(path, ':');
	if (!data.dirs)
		exit_gracefully(&data, MEMO_ERR);
	parse_input(&data, argc, argv);
	validate_input(&data);
	run(&data);
	exit_gracefully(&data, 0);
}
