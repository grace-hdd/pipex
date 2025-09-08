#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# ifndef NULL
#  define NULL ((void *)0)
# endif

# define READ_END 0
# define WRITE_END 1

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd1_args;
	char	**cmd2_args;
	char	*cmd1_path;
	char	*cmd2_path;
}	t_pipex;

// Main functions
void	pipex(t_pipex *data, char **argv, char **envp);
void	child_process1(t_pipex *data, char **envp);
void	child_process2(t_pipex *data, char **envp);

// Utility functions
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*get_cmd_path(char *cmd, char **envp);
void	free_array(char **array);
void	free_pipex(t_pipex *data);
void	error_exit(char *message, t_pipex *data);

// Libft functions
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

#endif
