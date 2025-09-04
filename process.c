/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex *data, char **envp)
{
	data->path1 = find_path(data->cmd1[0], envp);
	if (!data->path1)
		error_exit("Command not found", data);
	dup2(data->infile, STDIN_FILENO);
	dup2(data->pipe_fd[WRITE_END], STDOUT_FILENO);
	close_pipes(data);
	close(data->infile);
	close(data->outfile);
	execve(data->path1, data->cmd1, envp);
	error_exit("Execve failed", data);
}

void	second_child(t_pipex *data, char **envp)
{
	data->path2 = find_path(data->cmd2[0], envp);
	if (!data->path2)
		error_exit("Command not found", data);
	dup2(data->pipe_fd[READ_END], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close_pipes(data);
	close(data->infile);
	close(data->outfile);
	execve(data->path2, data->cmd2, envp);
	error_exit("Execve failed", data);
}
