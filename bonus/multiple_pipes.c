/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_multiple_pipes(t_pipex_bonus *data, int argc, char **argv, char **envp)
{
	init_multiple_pipes(data, argc, argv);
	create_pipes(data);
	execute_commands(data, envp);
	cleanup_multiple_pipes(data);
}

void	init_multiple_pipes(t_pipex_bonus *data, int argc, char **argv)
{
	int	i;

	data->cmd_count = argc - 3;
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		error_exit_bonus("Input file error", data);
	data->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->outfile == -1)
		error_exit_bonus("Output file error", data);
	data->pipes = malloc(sizeof(int *) * (data->cmd_count - 1));
	data->pids = malloc(sizeof(pid_t) * data->cmd_count);
	data->cmds = malloc(sizeof(char **) * data->cmd_count);
	data->paths = malloc(sizeof(char *) * data->cmd_count);
	if (!data->pipes || !data->pids || !data->cmds || !data->paths)
		error_exit_bonus("Memory allocation failed", data);
	i = 0;
	while (i < data->cmd_count)
	{
		data->cmds[i] = ft_split(argv[i + 2], ' ');
		if (!data->cmds[i])
			error_exit_bonus("Command parsing failed", data);
		i++;
	}
	data->here_doc = 0;
}

void	create_pipes(t_pipex_bonus *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			error_exit_bonus("Pipe allocation failed", data);
		if (pipe(data->pipes[i]) == -1)
			error_exit_bonus("Pipe creation failed", data);
		i++;
	}
}
