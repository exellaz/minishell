# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>

// cat < ../../TODO | grep command | wc -l || echo "You fucked" >> out.txt && echo "You successed !" >> out.txt
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	char *cmd[] =
	{
		"/bin/cat",
		"/usr/bin/grep",
		"/usr/bin/wc",
		"/bin/echo",
		"/bin/echo"
	};
	char *args[][3] =
	{
		{"cat", NULL, NULL},
		{"grep", "command", NULL},
		{"wc", "-l", NULL},
		{"echo", "You fucked", NULL},
		{"echo", "You successed !", NULL}
	};
	pid_t pid[5];
	int pipefd[2][2];
	int fd;
	int exit_status;

	pipe(pipefd[0]);
	pipe(pipefd[1]);
	pid[0] = fork();
	if (pid[0] == 0)	// cat < ../../TODO
	{
		close(pipefd[0][0]);
		close(pipefd[1][0]);
		close(pipefd[1][1]);
		fd = open("../../TODO", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		dup2(pipefd[0][1], STDOUT_FILENO);
		close(fd);
		close(pipefd[0][1]);
		execve(cmd[0], args[0], envp);
		perror("cat");
		exit(EXIT_FAILURE);
	}
	pid[1] = fork();
	if (pid[1] == 0)	// grep command
	{
		close(pipefd[0][1]);
		close(pipefd[1][0]);
		dup2(pipefd[0][0], STDIN_FILENO);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		execve(cmd[1], args[1], envp);
		perror("grep");
		exit(EXIT_FAILURE);
	}
	pid[2] = fork();
	if (pid[2] == 0)	// wc -l
	{
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		close(pipefd[1][1]);
		dup2(pipefd[1][0], STDIN_FILENO);
		close(pipefd[1][0]);
		execve(cmd[2], args[2], envp);
		perror("wc");
		exit(EXIT_FAILURE);
	}
	pid[3] = fork();
	if (pid[3] == 0)	// || echo "You fucked" >> out.txt
	{
		waitpid(pid[2], &exit_status, 0);
		if (!WIFEXITED(exit_status))
			exit(2);
		exit_status = WEXITSTATUS(exit_status);
		printf("exit_status[2]: %d\n", exit_status);
		if (exit_status == -1)
		{
			fd = open("out.txt", O_APPEND | O_WRONLY | O_CREAT, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			execve(cmd[3], args[3], envp);
			exit(EXIT_FAILURE);
		}
		exit(0);
	}
	pid[4] = fork();
	if (pid[4] == 0)	// && echo "You successed !" >> out.txt
	{
		waitpid(pid[3], &exit_status, 0);
		// if (!WIFEXITED(exit_status))
		// 	exit(2);
		exit_status = WEXITSTATUS(exit_status);
		printf("exit_status[3]: %d\n", exit_status);
		if (exit_status == 0)
		{
			fd = open("out.txt", O_APPEND | O_WRONLY | O_CREAT, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			execve(cmd[4], args[4], envp);
			exit(EXIT_FAILURE);
		}
		exit(0);
	}

	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[0][0]);
	close(pipefd[1][1]);

	for (int i = 0; i < 5; ++i)
	{
		waitpid(pid[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
		{
			exit_status = WEXITSTATUS(exit_status);
			printf("Success exit[%d]: %d\n", pid[i], exit_status);
		}
		else
			printf("Fail exit[%d]: %d\n", pid[i], exit_status);
	}

	return (0);
}
