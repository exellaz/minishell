/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:57:24 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/05 16:27:39 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include "define.h"
# include "libft.h"
# include "gbc.h"

int			print_builtin_err(char *builtin, char *cause, char *error);
int			print_err(char *cause, char *error);

t_wc_type	*gb_newtoken(t_wc_type token);
t_list		*gb_lstnew(void *content);
char		*gb_itoa(int n);
char		*gb_strdup(const char *s1);

int			find_pos(char *str, char delim);
char		*ft_strndup(char *str, int pos);
void		ft_strncpy(char *dst, char *src, int len);
int			is_space(char c);
int			is_quote(char c);
int			is_seperator(char *s);
void		skip_spaces(char **line);

void		show_tree(t_node *node, int depth, char *branch);
void		print_tree(t_node *node, int depth, char *branch);
void		print_arr(char **arr);
char		*get_node_type(int type);

# endif
