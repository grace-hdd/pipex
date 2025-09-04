/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_next_line(int fd)
{
	char	*line;
	char	buffer[2];
	int		bytes_read;
	int		i;

	line = malloc(sizeof(char) * 1000);
	if (!line)
		return (NULL);
	i = 0;
	while (1)
	{
		bytes_read = read(fd, buffer, 1);
		if (bytes_read <= 0)
			break;
		if (buffer[0] == '\n')
		{
			line[i] = '\n';
			line[i + 1] = '\0';
			return (line);
		}
		line[i] = buffer[0];
		i++;
	}
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}
