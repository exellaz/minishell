# pragma once

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct s_gbc
{
	int				id;
	void			*addr;
	struct s_gbc	*next;
}	t_gbc;

void	gb_clear(void);
void	*gb_malloc(size_t size);
void    *gb_add(void *addr);
t_gbc	*gb_collector(void);
void	gb_init(t_gbc *collector);

t_list	*gb_lstnew(void *content);
char	*gb_strdup(const char *s1);