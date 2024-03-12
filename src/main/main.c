/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:30:33 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/03/12 18:08:41 by jkhasiza         ###   ########.fr       */
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

void	parse_input(t_data *data, int argc, char **argv)
{
	int			fd;
	int			i;
	t_command	*cmd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		ft_putstr_fd(ACCESS_ERR_MSG, STDERR_FILENO);
	data->in_fd = fd;
	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit_gracefully(data, ACCESS_ERR, true);
	data->out_fd = fd;
	data->cmd_count = argc - 3;
	init_commands(data);
	init_pids(data);
	i = 2;
	while (i < argc - 1)
	{
		cmd = get_command(data, argv[i]);
		if (!cmd)
			exit_gracefully(data, MEMO_ERR, true);
		data->cmds[i - 2] = cmd;
		i++;
	}
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
	if (argc != 5)
		exit_gracefully(&data, USAGE_ERR, true);
	path = extract_path(envp);
	if (!path)
		exit_gracefully(&data, PATH_ERR, true);
	data.dirs = ft_split(path, ':');
	if (!data.dirs)
		exit_gracefully(&data, MEMO_ERR, true);
	parse_input(&data, argc, argv);
	run(&data);
	exit_gracefully(&data, data.exit_code, false);
}
