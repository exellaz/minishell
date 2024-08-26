# include "wildcard.h"

t_list	*ent_match(t_wildcard *wc, char *regex)
{
	t_list	*match_lst;
	t_list	*lst;
	char	*match;

	lst = wc->dirent->files;
	if (regex[0] == '.')
		lst = wc->dirent->dot_files;
	match_lst = NULL;
	while (lst)
	{
		match = pattern_match(lst->content, wc->token, wc->pattern);
		// DPRINTF("match: %s\n\n", match);
		if (match)
			ft_lstadd_back(&match_lst, gb_lstnew(gb_strdup(match)));
		lst = lst->next;
	}
	return (match_lst);
}

// returns the matched string or NULL if it doesn't match
char	*pattern_match(char *ent, t_token *token, char **pattern)
{
	char	*pos;
	char	*tmp;
	int		i;
	int		j;

	tmp = ent;
	j = -1;
	i = -1;
	while (token[++i] != T_END)
	{
		if (token[i] == T_PATTERN)
		{
			pos = ft_strnstr(tmp, pattern[++j], ft_strlen(tmp));
			if (!pos)
				return (NULL);
			if (i == 0 && pos != tmp)
				return (NULL);
			tmp = pos + ft_strlen(pattern[j]);
			// DPRINTF("token: %d\n", token[i + 1]);
			// DPRINTF("tmp: [%s]\n", tmp);
			if (token[i + 1] == T_END && *tmp != '\0')
				return (NULL);
		}
	}
	return (ent);
}
