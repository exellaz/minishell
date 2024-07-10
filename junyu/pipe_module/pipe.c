# include "pipe.h"

void	pipex(char *cmds[], char ***args, int fd[][2], int cmd_count)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < cmd_count + 1)
	{
		pid = fork();
		if (pid == 0)
		{
			redirect(fd, i, cmd_count);
			close_fds(fd, cmd_count - 1);
			execve(cmds[i], args[i], NULL);
			perror("execve");
			exit(0);
		}
	}
	close_fds(fd, cmd_count);
	i = -1;
	while (++i < cmd_count + 1)
		wait(NULL);
}

// not redirecting properly
void	redirect(int fd[][2], int i, int pipe_count)
{
	if (i > 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i < pipe_count)
		dup2(fd[i][1], STDOUT_FILENO);
}

/*
	First child			: close all fds except fd[0][1] (write end)
	Intermediate childs	: close all fds except fd[i - 1][0] (read end) fd[i][1] (write end)
	Last child			: close all fds except fd[last][0] (read end)
*/
void	close_fds(int fd[][2], int pipe_count)
{
	int	j;

	j = -1;
	while (++j < pipe_count)
	{
		close(fd[j][0]);
		close(fd[j][1]);
	}
}
