/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/10 15:56:34 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_wait;

int	main(int ac, char **av, char **envp)
{
	t_minishell	vars;

	(void)ac;
	init_vars(&vars, av[0], envp);
	while (1)
	{
		init_prompt(&vars);
		if (vars.line == NULL)
			break ;
		process_line(&vars);
		if (vars.token_list == NULL || vars.parse_err.type != E_NONE)
		{
			clear_ast(&vars.token_list, &vars.ast);
			continue ;
		}
		signal(SIGQUIT, int_sigquit);
		tcsetattr(STDIN_FILENO, TCSANOW, &vars.term);
		vars.exit_status = exec_node(vars.ast, false, &vars);
		clear_ast(&vars.token_list, &vars.ast);
	}
	clear(&vars);
	return (vars.exit_status);
}

int	process_line(t_minishell *vars)
{
	tokenize(vars->line, vars);
	if (vars->token_list == NULL)
		return (1);
	vars->ast = parse(vars);
	if (vars->parse_err.type != E_NONE)
	{
		handle_parse_error(vars);
		init_heredocs(vars->ast, vars);
		return (1);
	}
	init_heredocs(vars->ast, vars);
	return (0);
}

int	init_prompt(t_minishell *vars)
{
	setup_terminal(vars);
	if (isatty(fileno(stdin)))
		vars->line = gbc_add(readline("minishell> "));
	if (vars->line == NULL)
		ft_putstr_fd("exit\n", 2);
	if (vars->line == NULL)
		return (0);
	add_history(vars->line);
	return (0);
}

void	setup_terminal(t_minishell *vars)
{
	g_wait = 0;
	tcgetattr(STDIN_FILENO, &vars->term);
	vars->term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &vars->term);
	signal(SIGINT, int_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	init_vars(t_minishell *vars, char *name, char **envp)
{
	ft_bzero(vars, sizeof(t_minishell));
	vars->name = name;
	vars->env = dup_env(envp);
	vars->ms_stdin = dup(STDIN_FILENO);
	vars->ms_stdout = dup(STDOUT_FILENO);
}
