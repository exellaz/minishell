# include "exec.h"
# include "signal.h"
# include "gbc.h"
# include "define.h"

# define TEST 2

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);
	t_cmd_line	cmd;

	# if TEST == 1
	// cat -e << EOF | grep lol -v > out.txt
	cmd.redirs = gb_malloc(4 * sizeof(t_redir));
	cmd.redirs[0].type = T_HERE_DOC;
	cmd.redirs[0].file = "EOF";
	cmd.redirs[1].type = T_PIPE;
	cmd.redirs[1].file = NULL;
	cmd.redirs[2].type = T_REDOUT;
	cmd.redirs[2].file = "out.txt";
	cmd.redirs[3].type = T_END;
	cmd.redirs[3].file = NULL;

	cmd.cmds = gb_malloc(3 * sizeof(t_cmd));
		cmd.cmds[0].type = T_CMD;
		cmd.cmds[0].cmd = "/usr/bin/cat";
		cmd.cmds[0].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[0].argv[0] = "cat";
			cmd.cmds[0].argv[1] = "-e";
			cmd.cmds[0].argv[2] = NULL;
		cmd.cmds[1].type = T_CMD;
		cmd.cmds[1].cmd = "/usr/bin/grep";
		cmd.cmds[1].argv = gb_malloc(4 * sizeof(char *));
			cmd.cmds[1].argv[0] = "grep";
			cmd.cmds[1].argv[1] = "lol";
			cmd.cmds[1].argv[2] = "-v";
			cmd.cmds[1].argv[3] = NULL;
		cmd.cmds[2].type = T_END;
		cmd.cmds[2].cmd = NULL;
		cmd.cmds[2].argv = NULL;
	# endif
	# if TEST == 2
	// ls || echo hello world && cat define.h
	cmd.redirs = gb_malloc(3 * sizeof(t_redir));
		cmd.redirs[0].type = T_OR;
		cmd.redirs[0].file = NULL;
		cmd.redirs[1].type = T_AND;
		cmd.redirs[1].file = NULL;
		cmd.redirs[2].type = T_END;
		cmd.redirs[2].file = NULL;
	cmd.cmds = gb_malloc(4 * sizeof(t_cmd));
		cmd.cmds[0].type = T_CMD;
		cmd.cmds[0].cmd = "/usr/bin/ls";
		cmd.cmds[0].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[0].argv[0] = "ls";
			cmd.cmds[0].argv[1] = NULL;
			cmd.cmds[0].argv[2] = NULL;
		cmd.cmds[1].type = T_OR;
		cmd.cmds[1].cmd = "/usr/bin/echo";
		cmd.cmds[1].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[1].argv[0] = "echo";
			cmd.cmds[1].argv[1] = "hello world";
			cmd.cmds[1].argv[2] = NULL;
		cmd.cmds[2].type = T_AND;
		cmd.cmds[2].cmd = "/usr/bin/cat";
		cmd.cmds[2].argv = gb_malloc(3 * sizeof(char *));
			cmd.cmds[2].argv[0] = "cat";
			cmd.cmds[2].argv[1] = "define.h";
			cmd.cmds[2].argv[2] = NULL;
		cmd.cmds[3].type = T_END;
		cmd.cmds[3].cmd = NULL;
		cmd.cmds[3].argv = NULL;
	# endif

	execute(cmd.cmds, e);
	// cmd_exec(&cmd, e);

	gb_clear();
}
