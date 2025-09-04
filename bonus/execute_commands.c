/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_commands(t_pipex_bonus *data, char **envp)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		data->paths[i] = find_path(data->cmds[i][0], envp);
		if (!data->paths[i])
			error_exit_bonus("Command not found", data);
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			error_exit_bonus("Fork failed", data);
		if (data->pids[i] == 0)
			execute_child(data, i, envp);
		i++;
	}
	wait_for_children(data);
}

void	execute_child(t_pipex_bonus *data, int index, char **envp)
{
	if (index == 0)
		dup2(data->infile, STDIN_FILENO);
	else
		dup2(data->pipes[index - 1][0], STDIN_FILENO);
	if (index == data->cmd_count - 1)
		dup2(data->outfile, STDOUT_FILENO);
	else
		dup2(data->pipes[index][1], STDOUT_FILENO);
	close_all_pipes(data);
	close(data->infile);
	close(data->outfile);
	execve(data->paths[index], data->cmds[index], envp);
	error_exit_bonus("Execve failed", data);
}

void	wait_for_children(t_pipex_bonus *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
}
