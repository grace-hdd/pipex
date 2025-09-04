/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include "libft/libft.h"

# define READ_END 0
# define WRITE_END 1

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
}	t_pipex;

// Main functions
void	pipex(t_pipex *data, char **envp);
void	first_child(t_pipex *data, char **envp);
void	second_child(t_pipex *data, char **envp);

// Utility functions
void	init_data(t_pipex *data, char **argv);
void	parse_commands(t_pipex *data, char **argv);
char	*find_path(char *cmd, char **envp);
void	free_split(char **split);
void	free_data(t_pipex *data);
void	error_exit(char *msg, t_pipex *data);
void	close_pipes(t_pipex *data);

#endif
