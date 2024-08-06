# include "redir.h"
# include "env.h"
# include "libft.h"
# include "gbc.h"

# define TEST 5

int main(int ac, char **av, char **envp)
{

	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);

	// redin
	# if TEST == 1
	char	*cmd = "/bin/cat";
	char	*args[] = {"cat", "-e", NULL};
	int		fd = open("input.txt", O_RDONLY);

	redin(fd, cmd, args);
	# endif
	// redout
	# if TEST == 2
	char	*cmd = "/bin/echo";
	char	*args[] = {"echo", "Writing", "to", "output.txt...", NULL};
	int		fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	redout(fd, cmd, args);
	# endif
	// append
	# if TEST == 3
	char	*cmd = "/bin/echo";
	char	*args[] = {"echo", "Appending", "to", "output.txt...", NULL};
	int		fd = open("output.txt", O_APPEND | O_WRONLY | O_CREAT, 0644);

	redout(fd, cmd, args);
	# endif
	// heredoc
	# if TEST == 4
	char	*cmd = "/bin/cat";
	char	*args[] = {"cat", "-e", NULL};

	heredoc("eof", cmd, args);
	# endif
	// export
	char	*vars[] = {"a=1", "b=", "c", "d", NULL};
	# if TEST == 5
	// export(NULL, e);	printf("\n");
	export(vars, e);
	// export(NULL, e);	printf("\n");
	export((char *[]){"a=2", NULL}, e);
	env(e, VAR);	printf("\n");
	// export(NULL, e);	printf("\n");
	unset((char *[]){"a", "b", "c", "d", NULL}, e);
	export(NULL, e);	printf("\n");
	env(e, VAR);	printf("\n");
	# endif

	gb_clear();
}
