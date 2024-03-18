/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:30:33 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/18 19:23:31 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

char	*extract_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	run(t_data *data)
{
	init_pipes(data);
	run_commands(data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	t_data	data;

	init_data(&data, envp);
	if (argc < 5)
		exit_gracefully(&data, USAGE_ERR, USAGE_ERR_MSG, true);
	path = extract_path(envp);
	if (path)
	{
		data.dirs = ft_split(path, ':');
		if (!data.dirs)
			exit_gracefully(&data, MEMO_ERR, MEMO_ERR_MSG, true);
	}
	parse_input(&data, argc, argv);
	run(&data);
	exit_gracefully(&data, data.exit_code, "", false);
}
