/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:50:20 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/02/18 20:55:21 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/*
	Function initialies commands field and sets all items to
	`NULL`. This is needed to exit in the middle of the process
	if something goes south.
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
