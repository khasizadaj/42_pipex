/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:30:33 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/02/17 23:47:10 by jkhasiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

int	command_exists(char *command, char **dirs)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin(dirs[i], "/");
		if (!full_path)
			return (false);
		temp = full_path;
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (!full_path)
			return (false);
		if (access(full_path, X_OK) == 0)
			return (free(full_path), true);
		free(full_path);
		i++;
	}
	return (false);
}

/*
	Function vlaidates the inputs provided by the user. Like bash,
	it only informs the user about issues.
	
	Having errors doesn't stop the program from running except
	provided argument count is less than 4 (i.e. 5 with program name).
*/
int	validate_input(int argc, char **argv, char **dirs)
{
	int	i;

	if (argc < 5)
		return (USAGE_ERR);
	if (access(argv[1], R_OK) != 0)
		ft_putstr_fd(ACCESS_ERR_MSG, STDERR);
	i = 2;
	while (i < argc - 1)
	{
		if (!command_exists(argv[i], dirs))
			ft_putstr_fd(COMMAND_ERR_MSG, STDERR);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	t_data	data;

	init_data(&data);
	path = extract_path(envp);
	if (!path)
		exit_gracefully(&data, PATH_ERR);
	data.dirs = ft_split(path, ':');
	if (!data.dirs)
		exit_gracefully(&data, MEMO_ERR);
	data.exit_code = validate_input(argc, argv, data.dirs);
	if (data.exit_code != 0)
		exit_gracefully(&data, data.exit_code);
	exit_gracefully(&data, 0);
}
