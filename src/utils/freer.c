/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:02:12 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/02/18 15:23:28 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void    free_commmands(t_command **cmds)
{
    int i;

    i = 0;
    while (cmds[i])
    {
        // free path to command
        // free arguments (array of strings)
        // free struct
        ft_printf("Parse commands %d\n", i);
        free(cmds[i]);
        i++;
    }
    free(cmds);
}