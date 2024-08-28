/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:21:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/25 02:02:59 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_minishell *vars, char **envp)
{
	vars->token_list = NULL;
	vars->curr_token = NULL;
	vars->ast = NULL;
	vars->parse_err.type = E_NONE;
	vars->parse_err.str = NULL;
	vars->token_err = false;
	vars->line = NULL;
	vars->envp = envp;
	vars->env = dup_env(envp);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	vars;
	char	*curr_dir;

	((void)ac, (void)av);
	while (1)
	{
		init_vars(&vars, envp);
		curr_dir = fetch_val("PWD", vars.env);
		append_str(&curr_dir, "> ");
		vars.line = readline(curr_dir);
		// vars.line = readline("minishell: ");
		if (vars.line == NULL)
			break ;
		// if (*vars.line != '\0')
			add_history(vars.line);
		tokenize(vars.line, &vars);
		if (vars.token_list == NULL)
			continue ;
		// while (vars.token_list != NULL)
		// {
		// 	printf("value: %s\n", vars.token_list->value);
		// 	printf("type: %d\n", vars.token_list->type);
		// 	printf("-------------------------------------\n");
		// 	vars.token_list = vars.token_list->next;
		// }
		vars.ast = parse(&vars);
		if (vars.parse_err.type != E_NONE)
			handle_parse_error(&vars);
		expand_tree(vars.ast, 0, "root");
		exec_node(vars.ast, false, &vars);
		free(vars.line);
		clear_ast(&vars.token_list, &vars.ast);
	}
	// gb_clear();
	// clear_history();
	return (0);
}
