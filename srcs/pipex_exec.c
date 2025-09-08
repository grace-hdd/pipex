#include "pipex.h"

void	pipex(t_pipex *data, char **argv, char **envp)
{
	data->pid1 = fork();
	if (data->pid1 == -1)
		error_exit("Error: Fork failed", data);
	
	if (data->pid1 == 0)
		child_process1(data, envp);
	
	data->pid2 = fork();
	if (data->pid2 == -1)
		error_exit("Error: Fork failed", data);
	
	if (data->pid2 == 0)
		child_process2(data, envp);
	
	// Close pipe ends in parent
	close(data->pipe_fd[READ_END]);
	close(data->pipe_fd[WRITE_END]);
	
	// Wait for both child processes
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
}

void	child_process1(t_pipex *data, char **envp)
{
	// Redirect stdin to infile
	if (dup2(data->infile, STDIN_FILENO) == -1)
		error_exit("Error: Dup2 failed", data);
	
	// Redirect stdout to pipe write end
	if (dup2(data->pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		error_exit("Error: Dup2 failed", data);
	
	// Close unused file descriptors
	close(data->pipe_fd[READ_END]);
	close(data->pipe_fd[WRITE_END]);
	close(data->infile);
	close(data->outfile);
	
	// Execute first command
	if (execve(data->cmd1_path, data->cmd1_args, envp) == -1)
		error_exit("Error: Command execution failed", data);
}

void	child_process2(t_pipex *data, char **envp)
{
	// Redirect stdin to pipe read end
	if (dup2(data->pipe_fd[READ_END], STDIN_FILENO) == -1)
		error_exit("Error: Dup2 failed", data);
	
	// Redirect stdout to outfile
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		error_exit("Error: Dup2 failed", data);
	
	// Close unused file descriptors
	close(data->pipe_fd[READ_END]);
	close(data->pipe_fd[WRITE_END]);
	close(data->infile);
	close(data->outfile);
	
	// Execute second command
	if (execve(data->cmd2_path, data->cmd2_args, envp) == -1)
		error_exit("Error: Command execution failed", data);
}
