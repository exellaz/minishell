/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:50:19 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/08 13:17:29 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**insert_string_array(char **dest, char **src, int insert_index)
{
	int		dest_size;
	int		src_size;

	dest_size = count_strings(dest);
	src_size = count_strings(src);
	if (insert_index < 0 || insert_index > dest_size)
	{
		printf("Invalid insertion index.\n");
		return (NULL);
	}
	char	**new_dest = malloc((dest_size + src_size + 1) * sizeof(char *));
	if (new_dest == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < insert_index; i++)
	{
		new_dest[i] = (dest)[i];
	}
	for (int i = 0; i < src_size; i++)
	{
		new_dest[insert_index + i] = src[i];
	}
	for (int i = insert_index; i < dest_size; i++)
	{
		new_dest[src_size + i] = (dest)[i + 1];
	}
	new_dest[dest_size + src_size] = NULL;
	free(dest);
	return (new_dest);
}

int	find_pos(char *str, char delim)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != delim)
		;
	if (str[i] != delim)
		return (-1);
	return (i);
}

char	*ft_strndup(char *str, int pos)
{
	char	*dup;

	if (pos < 1)
		return (NULL);
	dup = gbc_malloc(pos + 1);
	ft_strncpy(dup, str, pos);
	return (dup);
}

void	ft_strncpy(char *dst, char *src, int len)
{
	int	i;

	i = -1;
	while (++i < len && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
}

void	skip_spaces(char **line)
{
	while (**line && is_space(**line))
		(*line)++;
}
