/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:13:20 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/16 19:09:22 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/*
	We create command count + 1 pipes to use. Every command
	will be intiliased in its own process.
*/
void	init_pipes(t_data *data)
{
	int	i;

	i = -1;
	data->pipes = ft_calloc(data->cmd_count - 1, sizeof(int *));
	if (!data->pipes)
		exit_gracefully(data, MEMO_ERR, MEMO_ERR_MSG, true);
	while (++i < data->cmd_count - 1)
	{
		data->pipes[i] = ft_calloc(2, sizeof(int));
		if (!data->pipes[i])
			exit_gracefully(data, MEMO_ERR, MEMO_ERR_MSG, true);
		if (pipe(data->pipes[i]) == -1)
			exit_gracefully(data, PIPE_ERR, PIPE_ERR_MSG, true);
	}
}
