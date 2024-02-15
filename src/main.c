/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:30:33 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/02/16 00:20:39 by jkhasiza         ###   ########.fr       */
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

int	validate_input(int argc, char **argv, char **dirs)
{
	int	i;

	if (argc < 5)
		return (ft_putstr_fd(USAGE_ERR_MSG, 2), USAGE_ERR);
	if (access(argv[1], R_OK) != 0)
		return (perror(ACCESS_ERR_MSG), ACCESS_ERR);
	if (access(argv[argc - 1], W_OK) != 0)
		return (perror(ACCESS_ERR_MSG), ACCESS_ERR);
	i = 2;
	while (i < argc - 1)
	{
		if (!command_exists(argv[i], dirs))
			return (perror(ACCESS_ERR_MSG), COMMAND_ERR);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**dirs;
	char	*path;
	int		exit_code;

	path = extract_path(envp);
	if (!path)
		return (perror(PATH_ERR_MSG), PATH_ERR);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (perror(MEMO_ERR_MSG), 13);
	exit_code = validate_input(argc, argv, dirs) != 0;
	if (exit_code != 0)
		exit(exit_code);
}
