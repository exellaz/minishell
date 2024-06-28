# include "commands.h"

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->identifiers[++i])
		printf("identifiers[%d]: %s\n", i, cmd->identifiers[i]);
	i = -1;
	while (cmd->tokens[++i])
		printf("tokens[%d]: %d\n", i, cmd->tokens[i]);
}