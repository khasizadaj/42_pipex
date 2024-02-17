/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:54:51 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/02/17 23:49:11 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	init_data(t_data *data)
{
	data->dirs = NULL;
	data->in_fd = -1;
	data->out_fd = -1;
	data->exit_code = UNKNOWN_ERR;
	return ;
}