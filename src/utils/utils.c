/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:14:41 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/12 21:35:28 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	handle_write_redirection(t_data *data, int i)
{
	if (i == data->cmd_count - 1)
	{
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
		{
			close_pipes(data);
			exit_gracefully(data, DUP2_OUT_ERR, DUP2_OUT_ERR_MSG, true);
		}
	}
	else
	{
		if (dup2(data->pipes[i + 1][1], STDOUT_FILENO) == -1)
		{
			close_pipes(data);
			exit_gracefully(data, DUP2_OUT_ERR, DUP2_OUT_ERR_MSG, true);
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
			exit_gracefully(data, ACCESS_ERR, ACCESS_ERR_MSG, false);
		}
		if (dup2(data->in_fd, STDIN_FILENO) == -1)
		{
			close_pipes(data);
			exit_gracefully(data, DUP2_IN_ERR, DUP2_IN_ERR_MSG, true);
		}
	}
	else
	{
		if (dup2(data->pipes[i][0], STDIN_FILENO) == -1)
		{
			close_pipes(data);
			exit_gracefully(data, DUP2_IN_ERR, DUP2_IN_ERR_MSG, true);
		}
	}
}

/*
	Function sets command path based on recieved `command`
	if first argument is a path. It modifies `command` struct
	directly and if something fails, it exits program directly.
*/
void	set_arg_as_path(t_data *data, t_command *command)
{
	if (access(command->args[0], X_OK) == 0)
	{
		command->path = ft_strdup(command->args[0]);
		if (!command->path)
			exit_gracefully(data, MEMO_ERR, MEMO_ERR_MSG, true);
	}
}

void	wait_for_processes(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->cmd_count)
	{
		waitpid(data->pids[i], &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
	}
}
