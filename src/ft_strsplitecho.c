/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitecho.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 22:10:27 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/09/29 15:32:43 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/minishell.h"

static int		ft_nextquote(char *s)
{
	char	c;
	int		i;

	c = s[0];
	i = 1;
	while (s[i] != c && s[i] != 0)
		i++;
	if (s[i] == 0)
		return (-1);
	else while (s[i] != c && s[i] != 0)
		i++;
	return (i);
}

char	**ft_arraypush(char **tab, char *str)
{
	int	i;
	int	n;
	char	**tmp;

	i = 0;
	while (tab[i])
		i++;
	tmp = (char **)ft_memalloc(sizeof(char*) * (i + 2));
	if (i > 0)
	{
		i = -1;
		while (tab[++i])
			tmp[i] = ft_strdup(tab[i]);
	}
	tmp[i] = ft_strdup(str);
	tmp[++i] = 0;
	ft_freetab(tab);
	return (tmp);
}

char	*ft_strjoinc(char *str, char c)
{
	char *tmp;
	char add[2];

	if (str && c)
	{
		add[0] = c;
		add[1] = '\0';
		tmp = ft_fstrjoin(str, add, 1);
	}
	else if (c)
	{
		add[0] = c;
		add[1] = '\0';
		tmp = ft_strdup(add);
	}
	else
	{
		tmp = ft_strdup(str);
		ft_memdel((void**)str);
		return (tmp);
	}
	return (tmp);
}

int		ft_strsplitecho(char ***tab, char const *s)
{
	char	*tmp;
	char	c;
	int		j;
	int		i;
	int		len;

	j = -1;
	if (s == NULL)
		return (0);
	*tab = (char **)ft_memalloc(sizeof(char*));
	**tab = 0;
	i = 0;
	tmp = NULL;
	while (s[i])
	{
		while (s[i] && ft_strchr(" \t", s[i]))
			i++;
		while (s[i] && !ft_strchr(" \t", s[i]))
		{
			if (ft_strchr("\'\"", s[i]))
			{
				c = s[i];
				i++;
				while (s[i] && s[i] != c)
					tmp = ft_strjoinc(tmp, s[i++]);
				if (s[i] != c)
					return (-1);
				i++;
			}
			else
				tmp = ft_strjoinc(tmp, s[i++]);
		}
		if (tmp)
		{
			*tab = ft_arraypush(*tab, tmp);
			ft_memdel((void**)&tmp);
		}
	}
	return (0);
}
