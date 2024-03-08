/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:14:41 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/08 18:15:47 by jkhasiza         ###   ########.fr       */
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
