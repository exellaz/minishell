# include "exec.h"
# include "debug.h"

int	cmd_exec(t_cmd_line *cmd, t_env *env)
{
	redirect(cmd->redirs);
	execute(cmd->cmds, env);
	return (0);
}

int	execute(t_cmd *cmds, t_env *env)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (cmds[++i].type != T_END)
	{
		if (i && cmds[i].type == T_AND)
			if (wait_status(pid, env) != 0)
				continue ;
		if (i && cmds[i].type == T_OR)
			if (wait_status(pid, env) == 0)
				continue ;
		pid = fork();
		if (pid == 0)
		{
			execve(cmds[i].cmd, cmds[i].argv, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	i = -1;
	while (cmds[++i].type != T_END)
		if (cmds[i].type == T_CMD)
			wait_status(pid, env);
	return (0);
}

int	redirect(t_redir *redirs)
{
	int	i;

	i = -1;
	while (redirs[++i].type != T_END)
	{
		// redirect
	}
	return (0);
}

// returns -1 on absense of pid
// returns -2 on abnormal termination
// returns the exit status of the child process (0-255)
int	wait_status(pid_t pid, t_env *env)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	else if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		set_val(env, "?", (char *)gb_add(ft_itoa(status)));
	}
	else
	{
		status = -2;
		printf("PID %d: terminated abnormally\n", pid);
	}
	return (status);
}
