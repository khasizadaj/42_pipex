/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:54:51 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/08 18:34:59 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	init_data(t_data *data, char **envp)
{
	data->dirs = NULL;
	data->pids = NULL;
	data->pipes = NULL;
	data->in_fd = -1;
	data->out_fd = -1;
	data->exit_code = UNKNOWN_ERR;
	data->cmd_count = -1;
	data->cmds = NULL;
	data->envp = envp;
	return ;
}
