/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:01:31 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/10 16:11:48 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	exit_for(int reason)
{
	if (reason == PATH_ERR)
		ft_putstr_fd(PATH_ERR_MSG, STDERR_FILENO);
	else if (reason == FORK_ERR)
		ft_putstr_fd(FORK_ERR_MSG, STDERR_FILENO);
	else if (reason == DUP2_IN_ERR)
		ft_putstr_fd(DUP2_IN_ERR_MSG, STDERR_FILENO);
	else if (reason == DUP2_OUT_ERR)
		ft_putstr_fd(DUP2_OUT_ERR_MSG, STDERR_FILENO);
	else if (reason == EXEC_ERR)
		ft_putstr_fd(EXEC_ERR_MSG, STDERR_FILENO);
	else if (reason == MEMO_ERR)
		ft_putstr_fd(MEMO_ERR_MSG, STDERR_FILENO);
	else if (reason == ACCESS_ERR)
		ft_putstr_fd(ACCESS_ERR_MSG, STDERR_FILENO);
	else if (reason == COMMAND_ERR)
		ft_putstr_fd(COMMAND_ERR_MSG, STDERR_FILENO);
	else if (reason == UNKNOWN_ERR)
		ft_putstr_fd(UNKNOWN_ERR_MSG, STDERR_FILENO);
	else if (reason == USAGE_ERR)
		ft_putstr_fd(USAGE_ERR_MSG, STDERR_FILENO);
	else if (reason == PIPE_ERR)
		ft_putstr_fd(PIPE_ERR_MSG, STDERR_FILENO);
	exit(reason);
}

void	exit_gracefully(t_data *data, int reason, bool with_message)
{
	if (data->dirs)
		free_dirs(data);
	if (data->pids)
		free(data->pids);
	if (data->pipes)
		free_pipes(data);
	if (data->cmds)
		free_commmands(data->cmds);
	if (with_message)
		exit_for(reason);
	else
		exit(reason);
}
