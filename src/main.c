/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhasiza <jkhasiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:30:33 by jkhasiza          #+#    #+#             */
/*   Updated: 2024/02/18 16:09:17 by jkhasiza         ###   ########.fr       */
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
int	validate_input(t_data *data, int argc, char **argv)
{
	int	i;

	if (argc < 5)
		return (USAGE_ERR);
	if (access(argv[1], R_OK) != 0)
		ft_putstr_fd(ACCESS_ERR_MSG, STDERR);
	i = 2;
	while (i < argc - 1)
	{
		if (!command_exists(argv[i], data->dirs))
			ft_putstr_fd(COMMAND_ERR_MSG, STDERR);
		i++;
	}
	return (0);
}

/*
	collect commands
	get pathes to commands
	save it struct array
*/
void	init_commands(t_data *data)
{
	int	i;

	data->cmds = malloc(sizeof(t_command) * (data->cmd_count + 1));
	if (!data->cmds)
		exit_gracefully(data, MEMO_ERR);
	i = -1;
	while (++i <= data->cmd_count)
		data->cmds[i] = NULL;
}

void	set_command_path(t_data *data, t_command *command)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = -1;
	while (data->dirs[++i])
	{
		full_path = ft_strjoin(data->dirs[i], "/");
		if (!full_path)
			exit_gracefully(data, MEMO_ERR);
		temp = full_path;
		if (!command->args)
			exit_gracefully(data, MEMO_ERR);
		full_path = ft_strjoin(temp, command->args[0]);
		free(temp);
		if (!full_path)
			exit_gracefully(data, MEMO_ERR);
		if (access(full_path, X_OK) == 0)
		{
			command->path = full_path;
			return ;
		}
		free(full_path);
	}
}

/*
	Function returns struct of path and arguments will be
	used for it.
	
	If `path` is `NULL`, that means command cannot be used
	and it should be skipped.
*/
t_command	*get_command(t_data *data, char *raw_command)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->args = ft_split(raw_command, ' ');
	if (!cmd->args)
		return (NULL);
	set_command_path(data, cmd);
	return (cmd);
}

void	parse_input(t_data *data, int argc, char **argv)
{
	int			fd;
	int			i;
	t_command	*cmd;

	fd = open(argv[1], O_RDONLY);
	if (fd != -1)
		data->in_fd = fd;
	fd = open(argv[argc - 1], O_WRONLY);
	if (fd != -1)
		data->out_fd = fd;
	data->cmd_count = argc - 3;
	init_commands(data);
	i = 2;
	while (i < argc - 1)
	{
		cmd = get_command(data, argv[i]);
		if (!cmd)
			exit_gracefully(data, MEMO_ERR);
		data->cmds[i - 2] = cmd;
		i++;
	}
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
	data.exit_code = validate_input(&data, argc, argv);
	if (data.exit_code != 0)
		exit_gracefully(&data, data.exit_code);
	parse_input(&data, argc, argv);
	exit_gracefully(&data, 0);
}
