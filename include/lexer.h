/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:11 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 12:47:16 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <readline/readline.h>
# include <stdbool.h>
# include "define.h"
# include "libft.h"

# define OPERATORS_SET "|><()"

bool	append_operator_token(t_token_type type, char **line, t_token **token_list);
bool	handle_operator_token(char **line, t_token **list);
t_token	*init_new_token(t_token_type type, char *value);
void	add_token_to_list(t_token **token_list, t_token *token);
bool	is_quote_closed(char *line, int	*i);
void	clear_token_list(t_token **token_list);
void	tokenize(char *line, t_minishell *vars);
void	handle_quote_err(char quote, t_minishell *vars);
void	handle_open_quote(char **line, char **buffer, int *char_count, char quote);
bool	append_word_token(char **line, t_token **token_list, t_minishell *vars);
bool	is_quote_balance(char *str, char quote);
char	get_quote_type(char *str);
void	skip_quote_string(char *line, int *i);
bool	init_word_token(char **line, char *buffer, int count, t_token **lst);

#endif
