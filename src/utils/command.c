/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:50:20 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/12 21:33:03 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/*
	Function initialies commands field and sets all items to
	`NULL`. This is needed to exit in the middle of the process
	if something goes south.

	Note: It also null terminates the array.
*/
void	init_commands(t_data *data)
{
	int	i;

	data->cmds = malloc(sizeof(t_command *) * (data->cmd_count + 1));
	if (!data->cmds)
		exit_gracefully(data, MEMO_ERR, MEMO_ERR_MSG, true);
	i = -1;
	while (++i <= data->cmd_count)
		data->cmds[i] = NULL;
}

void	init_pids(t_data *data)
{
	int	i;

	data->pids = malloc(sizeof(int) * (data->cmd_count + 1));
	if (!data->pids)
		exit_gracefully(data, MEMO_ERR, MEMO_ERR_MSG, true);
	i = -1;
	while (++i <= data->cmd_count)
		data->pids[i] = 0;
}

/*
	Function sets command path based on recieved `command`.
	It modifies `command` struct directly and if something
	fails, it exits program directly.
*/
static void	set_command_path(t_data *data, t_command *command)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = -1;
	while (data->dirs[++i])
	{
		full_path = ft_strjoin(data->dirs[i], "/");
		if (!full_path)
			exit_gracefully(data, MEMO_ERR, MEMO_ERR_MSG, true);
		temp = full_path;
		full_path = ft_strjoin(temp, command->args[0]);
		free(temp);
		if (!full_path)
			exit_gracefully(data, MEMO_ERR, MEMO_ERR_MSG, true);
		if (access(full_path, X_OK) == 0)
		{
			command->path = full_path;
			return ;
		}
		free(full_path);
	}
	set_arg_as_path(data, command);
	if (chr_in('/', command->args[0]) == 1)
		return ;
}

/*
	Function returns struct of path and arguments will be
	used for it.
	
	If `path` is `NULL`, that means command cannot be used
	and it should be skipped.
*/
t_command	*get_command(t_data *data, char *raw_command)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->args = ft_split(raw_command, ' ');
	if (!cmd->args)
		return (free(cmd), NULL);
	set_command_path(data, cmd);
	return (cmd);
}

void	run_commands(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			exit_gracefully(data, FORK_ERR, MEMO_ERR_MSG, true);
		if (data->pids[i] == 0)
		{
			handle_read_redirection(data, i);
			handle_write_redirection(data, i);
			close_pipes(data);
			if (!data->cmds[i]->path)
				exit_gracefully(data, COMMAND_ERR, COMMAND_ERR_MSG, true);
			if (execve(data->cmds[i]->path,
					data->cmds[i]->args, data->envp) == -1)
				exit_gracefully(data, EXEC_ERR, EXEC_ERR_MSG, true);
		}
	}
	close_pipes(data);
	wait_for_processes(data);
}
