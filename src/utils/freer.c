/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:02:12 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/07 17:00:57 by jkhasiza         ###   ########.fr       */
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

void	close_pipes(t_data *data)
{
	int j;

	j = -1;
	while (++j < data->cmd_count)
	{
		printf("Closed pipe[%d][0] = %d\n", j, data->pipes[j][0]);
		close(data->pipes[j][0]);
		printf("Closed pipe[%d][1] = %d\n", j, data->pipes[j][1]);			
		close(data->pipes[j][1]);
	}
	if (data->in_fd != -1)
	{
		printf("Closed infile: %d\n", data->in_fd);			
		close(data->in_fd);
	}
	if (data->out_fd != -1)
	{
		printf("Closed outfile: %d\n", data->out_fd);			
		close(data->out_fd);
	}
}

// void	close_pipes(t_data *data, int child_proc_id, bool close_all)
// {
// 	int j;

// 	j = -1;
// 	while (++j < data->cmd_count)
// 	{
// 		if ((child_proc_id == 0 && j == 0) || child_proc_id != j)
// 		{
// 			printf("Closed pipe[%d][0] = %d\n", j, data->pipes[j][0]);
// 			close(data->pipes[j][0]);
// 		}
// 		if ((child_proc_id == data->cmd_count - 1 && j == data->cmd_count - 1) || (child_proc_id + 1 != j))
// 		{
// 			printf("Closed pipe[%d][1] = %d\n", j, data->pipes[j][1]);			
// 			close(data->pipes[j][1]);
// 		}
// 	}
// 	if (close_all)
// 	{
// 		printf("Closed pipe[%d][1] = %d\n", child_proc_id, data->pipes[child_proc_id][0]);			
// 		printf("Closed pipe[%d][1] = %d\n", child_proc_id + 1, data->pipes[child_proc_id + 1][1]);			
// 		close(data->pipes[child_proc_id][0]);
// 		close(data->pipes[child_proc_id + 1][1]);
// 		if (data->in_fd != -1)
// 		{
// 			printf("Closed infile: %d\n", data->in_fd);			
// 			close(data->in_fd);
// 		}
// 		if (data->out_fd != -1)
// 		{
// 			printf("Closed outfile: %d\n", data->out_fd);			
// 			close(data->out_fd);
// 		}
// 	}
// }
