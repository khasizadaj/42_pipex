/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:02:12 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/02/18 21:38:28 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	free_commmands(t_command **cmds)
{
	int			i;
	int			j;
	t_command	*temp;

	i = 0;
	while (cmds[i])
	{
		temp = cmds[i];
		if (temp->path)
			free(temp->path);
		if (temp->args)
		{
			j = -1;
			while (temp->args[++j])
				free(temp->args[j]);
			free(temp->args);
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	free_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count + 1 && data->pipes[i])
		{
			free(data->pipes[i]);
			i++;
		}
		free(data->pipes);
}

void	free_dirs(t_data *data)
{
	int	i;

	i = -1;
	while (data->dirs[++i])
		free(data->dirs[i]);
	free(data->dirs);
}
