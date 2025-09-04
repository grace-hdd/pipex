/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

typedef struct s_pipex_bonus
{
	int		infile;
	int		outfile;
	int		**pipes;
	int		cmd_count;
	pid_t	*pids;
	char	***cmds;
	char	**paths;
	int		here_doc;
	char	*limiter;
}	t_pipex_bonus;

// Multiple pipes functions
void	handle_multiple_pipes(t_pipex_bonus *data, int argc, char **argv, char **envp);
void	init_multiple_pipes(t_pipex_bonus *data, int argc, char **argv);
void	create_pipes(t_pipex_bonus *data);
void	execute_commands(t_pipex_bonus *data, char **envp);
void	cleanup_multiple_pipes(t_pipex_bonus *data);

// Here document functions
void	handle_here_doc(t_pipex_bonus *data, int argc, char **argv, char **envp);
void	init_here_doc(t_pipex_bonus *data, int argc, char **argv);
void	write_here_doc(t_pipex_bonus *data);
void	execute_here_doc(t_pipex_bonus *data, char **envp);
void	cleanup_here_doc(t_pipex_bonus *data);

// Bonus utility functions
void	execute_child(t_pipex_bonus *data, int index, char **envp);
void	wait_for_children(t_pipex_bonus *data);
void	close_all_pipes(t_pipex_bonus *data);
void	error_exit_bonus(char *msg, t_pipex_bonus *data);
char	*get_next_line(int fd);

#endif
