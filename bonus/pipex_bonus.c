/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
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
	t_pipex_bonus	data;

	if (argc < 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 48);
		write(2, "       ./pipex here_doc LIMITER cmd1 cmd2 file\n", 48);
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		handle_here_doc(&data, argc, argv, envp);
	else
		handle_multiple_pipes(&data, argc, argv, envp);
	return (0);
}
