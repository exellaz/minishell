/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:03:14 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/28 11:32:05 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GBC_H
# define GBC_H

# include <stdlib.h>
# include "libft.h"
# include "wildcard.h"
# include "define.h"

void	gb_clear(void);
void	*gb_malloc(size_t size);
void	gb_free(void *addr);
t_gbc	*gb_collector(void);
void	gb_init(t_gbc *collector);
void	*gb_add(void *addr);

t_wc_type	*gb_newtoken(t_wc_type token);
t_list	*gb_lstnew(void *content);
char	*gb_strdup(const char *s1);
#endif
