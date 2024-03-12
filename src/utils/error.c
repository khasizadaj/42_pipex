/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:01:31 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/12 21:31:21 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	exit_for(int reason, char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(reason);
}

void	exit_gracefully(t_data *data, int reason, char *msg, bool with_message)
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
		exit_for(reason, msg);
	else
		exit(reason);
}
