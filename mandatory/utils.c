/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_pipex *data, char **argv)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		error_exit("Input file error", data);
	data->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->outfile == -1)
		error_exit("Output file error", data);
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->path1 = NULL;
	data->path2 = NULL;
	parse_commands(data, argv);
}

void	parse_commands(t_pipex *data, char **argv)
{
	data->cmd1 = ft_split(argv[2], ' ');
	data->cmd2 = ft_split(argv[3], ' ');
	if (!data->cmd1 || !data->cmd2)
		error_exit("Command parsing failed", data);
}

void	free_data(t_pipex *data)
{
	int	i;

	if (data->cmd1)
	{
		i = 0;
		while (data->cmd1[i])
			free(data->cmd1[i++]);
		free(data->cmd1);
	}
	if (data->cmd2)
	{
		i = 0;
		while (data->cmd2[i])
			free(data->cmd2[i++]);
		free(data->cmd2);
	}
	if (data->path1)
		free(data->path1);
	if (data->path2)
		free(data->path2);
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
}

void	error_exit(char *msg, t_pipex *data)
{
	perror(msg);
	free_data(data);
	exit(1);
}

void	close_pipes(t_pipex *data)
{
	close(data->pipe_fd[READ_END]);
	close(data->pipe_fd[WRITE_END]);
}
