/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 22:10:27 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/09/17 22:19:19 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/minishell.h"

static size_t	ft_count_word(char const *s)
{
	size_t	ret;
	size_t	i;

	ret = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '\t' && (s[i + 1] == ' ' || s[i + 1] == '\t'|| s[i + 1] == '\0'))
			ret++;
		i++;
	}
	return (ret);
}

static size_t	ft_len_word(char const *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
		i++;
	return (i);
}

char			**ft_strsplitshell(char const *s)
{
	char	**tab;
	int		j;
	int		len;
	int		count_word;

	j = -1;
	if (s == NULL)
		return (NULL);
	count_word = ft_count_word(s);
	if ((tab = (char **)malloc(sizeof(char *) * (count_word + 1))) == NULL)
		msgexit("error malloc: function(ft_strsplitshell)");
	while (++j < count_word)
	{
		while (*s != '\0' && (*s == ' ' || *s == '\t'))
			s++;
		len = ft_len_word(s);
		if ((tab[j] = (char *)ft_memalloc(sizeof(char) * (len + 1))) == NULL)
			msgexit("error malloc: function(ft_strsplitshell)");
		ft_strncpy(tab[j], s, len);
		while (*s != '\0' && *s != ' ' && *s != '\t')
			s++;
	}
	tab[j] = 0;
	return (tab);
}
