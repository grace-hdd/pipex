/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_here_doc(t_pipex_bonus *data, int argc, char **argv, char **envp)
{
	init_here_doc(data, argc, argv);
	write_here_doc(data);
	execute_here_doc(data, envp);
	cleanup_here_doc(data);
}

void	init_here_doc(t_pipex_bonus *data, int argc, char **argv)
{
	int	i;

	data->here_doc = 1;
	data->limiter = argv[2];
	data->cmd_count = argc - 4;
	data->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
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
		data->cmds[i] = ft_split(argv[i + 3], ' ');
		if (!data->cmds[i])
			error_exit_bonus("Command parsing failed", data);
		i++;
	}
}

void	write_here_doc(t_pipex_bonus *data)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		error_exit_bonus("Pipe creation failed", data);
	data->infile = pipe_fd[1];
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (!line)
			break;
		if (ft_strncmp(line, data->limiter, ft_strlen(data->limiter)) == 0)
		{
			free(line);
			break;
		}
		write(data->infile, line, ft_strlen(line));
		free(line);
	}
	close(data->infile);
	data->infile = pipe_fd[0];
}

void	execute_here_doc(t_pipex_bonus *data, char **envp)
{
	create_pipes(data);
	execute_commands(data, envp);
}
