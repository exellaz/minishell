/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:31:48 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/29 11:07:26 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <readline/readline.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include "define.h"
# include "gbc.h"

void	expand_tree(t_node *node, int depth, char *branch, t_minishell *vars);
void	expand_node(t_node *node, t_minishell *vars);
char	**expand_args(char *args, t_minishell *vars);
char	*expand_params(char	*str);
char	*handle_squote(char *str, int *i);
char	*handle_dquote(char *str, int *i);
char	*handle_reg_str(char *str, int *i);
char	*handle_dollar(char *str, int *i);
bool	is_valid_var_char(char c);
t_env	*dup_env(char *envp[]);
void	env(t_env *e, char lst);
void	unset(char **keys, t_env *v);
void	add_ent(t_env *e, char *key, char *val);
int		find_pos(char *str, char delim);
char	**split_ent(char *str);
char	*ft_strndup(char *str, int pos);
void	set_val(t_env *e, char *key, char *val);
void	ft_strncpy(char *dst, char *src, int len);
char	*fetch_val(char *key, t_env *e);

void	append(char *file, char *cmd, char *args[]);
void	write_file(char *file, char *content);
char	*read_pipe(int read_fd);
void	append_str(char **str1, char *str2);

char	*parse_path(char *envp[], char *cmd);
void	trim_path(char *cmd, char *path);
void	prepend_cmd(char **path_list, char *cmd);

char	**split_args(char *str);
int		count_words(char *str);
void	skip_word(char *str, int *i);
char	**allocate_args(char *str, char **args);
char	**fill_args(char *str, char **args);
void	fill_word(char *str, char **args, int *i, int j);

void	heredoc(t_io_node *io, int *p_fd);
char	*read_doc(char *delimiter);

char *remove_quotes(char *str);

#endif