/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:32:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 12:50:46 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_quote_closed(char *line, int	*i)
{
	char	quote_type;

	quote_type = line[*i];
	if (ft_strchr(line + *i + 1, quote_type))
	{
		(*i)++;
		while ((line[*i]) != quote_type)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}

void	skip_quote_string(char *line, int *i)
{
	char	quote_type;

	quote_type = line[*i];
	(*i)++;
	while (line[*i] != quote_type)
		(*i)++;
	(*i)++;
}
