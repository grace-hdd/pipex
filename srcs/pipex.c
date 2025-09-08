#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(1);
	}
	
	// Initialize pipex structure
	data.infile = open(argv[1], O_RDONLY);
	if (data.infile == -1)
		error_exit("Error: Cannot open infile", &data);
	
	data.outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data.outfile == -1)
		error_exit("Error: Cannot create/open outfile", &data);
	
	if (pipe(data.pipe_fd) == -1)
		error_exit("Error: Pipe creation failed", &data);
	
	// Parse commands
	data.cmd1_args = ft_split(argv[2], ' ');
	data.cmd2_args = ft_split(argv[3], ' ');
	
	if (!data.cmd1_args || !data.cmd2_args)
		error_exit("Error: Command parsing failed", &data);
	
	// Get command paths
	data.cmd1_path = get_cmd_path(data.cmd1_args[0], envp);
	data.cmd2_path = get_cmd_path(data.cmd2_args[0], envp);
	
	if (!data.cmd1_path || !data.cmd2_path)
		error_exit("Error: Command not found", &data);
	
	// Execute pipex
	pipex(&data, argv, envp);
	
	// Clean up
	free_pipex(&data);
	return (0);
}
