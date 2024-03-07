/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:50:20 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/07 19:39:29 by jkhasiza         ###   ########.fr       */
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

	data->cmds = malloc(sizeof(t_command) * (data->cmd_count + 1));
	if (!data->cmds)
		exit_gracefully(data, MEMO_ERR);
	i = -1;
	while (++i <= data->cmd_count)
		data->cmds[i] = NULL;
}

void	init_pids(t_data *data)
{
	int	i;

	data->pids = malloc(sizeof(int) * (data->cmd_count + 1));
	if (!data->pids)
		exit_gracefully(data, MEMO_ERR);
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
	if (access(command->args[0], X_OK) == 0)
	{
		command->path = ft_strdup(command->args[0]);
		if (!command->path)
			exit_gracefully(data, MEMO_ERR);
		return ;
	}
	while (data->dirs[++i])
	{
		full_path = ft_strjoin(data->dirs[i], "/");
		if (!full_path)
			exit_gracefully(data, MEMO_ERR);
		temp = full_path;
		if (!command->args)
			exit_gracefully(data, MEMO_ERR);
		full_path = ft_strjoin(temp, command->args[0]);
		free(temp);
		if (!full_path)
			exit_gracefully(data, MEMO_ERR);
		if (access(full_path, X_OK) == 0)
		{
			command->path = full_path;
			return ;
		}
		free(full_path);
	}
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
		return (NULL);
	set_command_path(data, cmd);
	return (cmd);
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
