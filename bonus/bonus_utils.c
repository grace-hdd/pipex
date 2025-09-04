/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	cleanup_multiple_pipes(t_pipex_bonus *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		free(data->pipes[i]);
		i++;
	}
	free(data->pipes);
	free(data->pids);
	i = 0;
	while (i < data->cmd_count)
	{
		free_split(data->cmds[i]);
		free(data->paths[i]);
		i++;
	}
	free(data->cmds);
	free(data->paths);
	close(data->infile);
	close(data->outfile);
}

void	cleanup_here_doc(t_pipex_bonus *data)
{
	cleanup_multiple_pipes(data);
	free(data->limiter);
}

void	close_all_pipes(t_pipex_bonus *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

void	error_exit_bonus(char *msg, t_pipex_bonus *data)
{
	perror(msg);
	if (data->here_doc)
		cleanup_here_doc(data);
	else
		cleanup_multiple_pipes(data);
	exit(1);
}
