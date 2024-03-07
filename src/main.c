/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:30:33 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/07 17:07:25 by jkhasiza         ###   ########.fr       */
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
	i = 2;
	while (i < argc - 1)
	{
		if (!command_exists(argv[i], data->dirs))
			ft_putstr_fd(COMMAND_ERR_MSG, STDERR_FILENO);
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

void	run_commands(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->cmd_count)
	{
		printf("Process %d\n\n", i);
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			exit_gracefully(data, FORK_ERR);
		if (data->pids[i] == 0)
		{
			if (i == 0)
			{
				if (data->in_fd == -1 && dup2(data->in_fd, STDIN_FILENO) == -1)
				{
					printf("\n\nExiting 1\n\n");
					close_pipes(data);
					exit_gracefully(data, 100);
				}
			}	
			else
			{
				if (dup2(data->pipes[i][0], STDIN_FILENO) == -1)
				{
					printf("\n\nExiting 2\n\n");
					close_pipes(data);
					exit_gracefully(data, 101);
				}
			}
			printf("\n\nTowrds the end\n\n");
			if (i == data->cmd_count - 1)
			{
				printf("\nRedir for second command: %d\n\n", data->out_fd);
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
			close_pipes(data);
			if (!data->cmds[i]->path)
				return ;
			if (execve(data->cmds[i]->path, data->cmds[i]->args, data->envp) == -1)
				exit_gracefully(data, EXEC_ERR);
		}
	}

	i = -1;
	while (++i < data->cmd_count)
	{
		waitpid(data->pids[i], &status, 0);
		printf("PARENT: Child: %d returned value is: %d\n", i, WEXITSTATUS(data->pids[i]));
	}

	printf("MAIN PROCESS\n");
	close_pipes(data);
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
	run(&data);
	exit_gracefully(&data, 0);
}
