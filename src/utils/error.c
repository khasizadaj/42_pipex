/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:01:31 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/07 01:12:12 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	exit_for(int reason)
{
	if (reason == PATH_ERR)
		perror(PATH_ERR_MSG);
	else if (reason == EXEC_ERR)
		perror(EXEC_ERR_MSG);
	else if (reason == MEMO_ERR)
		perror(MEMO_ERR_MSG);
	else if (reason == ACCESS_ERR)
		perror(ACCESS_ERR_MSG);
	else if (reason == COMMAND_ERR)
		perror(COMMAND_ERR_MSG);
	else if (reason == UNKNOWN_ERR)
		perror(UNKNOWN_ERR_MSG);
	else if (reason == USAGE_ERR)
		perror(USAGE_ERR_MSG);
	else if (reason == PIPE_ERR)
		perror(PIPE_ERR_MSG);
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
