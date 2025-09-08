#include "pipex.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*cmd_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	
	if (!envp[i])
		return (NULL);
	
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	
	free_array(paths);
	return (NULL);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return;
	
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_pipex(t_pipex *data)
{
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
	if (data->pipe_fd[0] != -1)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		close(data->pipe_fd[1]);
	
	free_array(data->cmd1_args);
	free_array(data->cmd2_args);
	free(data->cmd1_path);
	free(data->cmd2_path);
}

void	error_exit(char *message, t_pipex *data)
{
	ft_putendl_fd(message, 2);
	free_pipex(data);
	exit(1);
}
