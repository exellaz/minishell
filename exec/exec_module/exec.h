# pragma once

# include "pipe.h"
# include "redir.h"
# include "env.h"
# include "libft.h"
# include "define.h"

/*
 regular commands (cmd operator), set field `type` to:
		T_CMD, T_REDOUT, T_APPEND, T_PIPE
 for && and || commands (logical command), set to field `logical`
 field `cmd` should be the full path of the command
 field `argv` should be NULL terminated
*/
typedef struct s_cmd
{
	t_token	logical;
	t_token	type;
	char	*cmd;
	char	**argv;
}	t_cmd;

// for T_HERE_DOC, set field `file` to the delimiter
// for T_PIPE, set field `file` to NULL
typedef struct s_redir
{
	t_token		type;
	char		*file;
}	t_redir;

// both fields should be terminated by type: T_END
typedef struct s_cmd_line
{
	t_redir	*redirs;
	t_cmd	*cmds;
	t_list	*fds;
}	t_cmd_line;

int	cmd_exec(t_cmd_line *cmd, t_env *env);
int	execute(t_cmd *cmds, t_env *env, t_list *fds);
int	redirect(t_redir *redirs, t_list **fds);
int	close_fd(t_env *env, t_token type, pid_t pid, t_list *fds);
int	wait_status(pid_t pid, t_env *env);
