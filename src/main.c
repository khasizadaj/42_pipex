/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:30:33 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/05 20:51:37 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>

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

int	command_exists(char *command, char **dirs)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin(dirs[i], "/");
		if (!full_path)
			return (false);
		temp = full_path;
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (!full_path)
			return (false);
		if (access(full_path, X_OK) == 0)
			return (free(full_path), true);
		free(full_path);
		i++;
	}
	return (false);
}

/*
	Function vlaidates the inputs provided by the user. Like bash,
	it only informs the user about issues.
	
	Having errors doesn't stop the program from running except
	provided argument count is less than 4 (i.e. 5 with program name).
*/
int	validate_input(t_data *data, int argc, char **argv)
{
	int	i;

	if (argc < 5)
		return (USAGE_ERR);
	if (access(argv[1], R_OK) != 0)
		ft_putstr_fd(ACCESS_ERR_MSG, STDERR);
	i = 2;
	while (i < argc - 1)
	{
		if (!command_exists(argv[i], data->dirs))
			ft_putstr_fd(COMMAND_ERR_MSG, STDERR);
		i++;
	}
	return (0);
}

void	parse_input(t_data *data, int argc, char **argv)
{
	int			fd;
	int			i;
	t_command	*cmd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		exit_gracefully(data, ACCESS_ERR);
	data->in_fd = fd;
	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit_gracefully(data, ACCESS_ERR);
	data->out_fd = fd;
	data->cmd_count = argc - 3;
	init_commands(data);
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

void	run_commands(t_data *data)
{
	int	i;
	int	pid;
	int	status;

	i = 0;
	status = 0;
	printf("CMD COUNT: %d\n", data->cmd_count);
	while (i < data->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			exit_gracefully(data, FORK_ERR);
		if (pid == 0)
		{
			close(data->pipes[i][1]); // close more later
			if (i == 0)
				dup2(data->in_fd, data->pipes[i][0]);
			else
				dup2(data->pipes[i][0], STDIN_FILENO);
			close(data->pipes[i][0]);
			close(data->in_fd);

			if (i == data->cmd_count - 1)
			{
				dup2(data->out_fd, STDOUT_FILENO);
			}
			else
			{
				dup2(data->pipes[i + 1][1], STDOUT_FILENO);
				close(data->pipes[i + 1][1]);
			}
			close(data->pipes[i][0]); // close more later
			close(data->pipes[i+ 1][1]); // close more later
			execve(data->cmds[i]->path, data->cmds[i]->args, data->envp);
		}
		else
		{
			close(data->pipes[i][1]); // close more later
			close(data->pipes[i][0]);
		}
		i++;
	}
	i = -1;
	while (++i < data->cmd_count)
		wait(NULL);
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
	path = extract_path(envp);
	if (!path)
		exit_gracefully(&data, PATH_ERR);
	data.dirs = ft_split(path, ':');
	if (!data.dirs)
		exit_gracefully(&data, MEMO_ERR);
	data.exit_code = validate_input(&data, argc, argv);
	if (data.exit_code != 0)
		exit_gracefully(&data, data.exit_code);
	parse_input(&data, argc, argv);
	dup2(data.in_fd, STDIN_FILENO);
	run(&data);
}
