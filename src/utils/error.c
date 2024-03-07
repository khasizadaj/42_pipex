/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:01:31 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/07 13:06:22 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"
#include <unistd.h>

static void	exit_for(int reason)
{
	if (reason == PATH_ERR)
		ft_putstr_fd(PATH_ERR_MSG, STDERR_FILENO);
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

void	exit_gracefully(t_data *data, int reason)
{
	if (data->dirs)
		free_dirs(data);
	if (data->pipes)
		free_pipes(data);
	if (data->cmds)
		free_commmands(data->cmds);
	exit_for(reason);
}
