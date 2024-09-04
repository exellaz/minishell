#include "utils.h"

int	print_builtin_err(char *builtin, char *cause, char *error)
{
	if (!cause)
		return (0);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(builtin, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(cause, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

int	print_err(char *cause, char *error)
{
	if (!cause)
		return (0);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cause, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}