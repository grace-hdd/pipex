/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
		exit(1);
	}
	init_data(&data, argv);
	if (pipe(data.pipe_fd) == -1)
		error_exit("Pipe creation failed", &data);
	data.pid1 = fork();
	if (data.pid1 == -1)
		error_exit("Fork failed", &data);
	if (data.pid1 == 0)
		first_child(&data, envp);
	data.pid2 = fork();
	if (data.pid2 == -1)
		error_exit("Fork failed", &data);
	if (data.pid2 == 0)
		second_child(&data, envp);
	close_pipes(&data);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	free_data(&data);
	return (0);
}
