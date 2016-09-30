/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 18:04:33 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/09/30 18:06:09 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

char	**getpath(char *name, t_env **env)
{
	char	**tab;
	t_env	*elem;

	tab = NULL;
	if ((elem = findvar(name, env)) && elem->value)
	{
		tab = ft_strsplit(elem->value, ':');
		if (!tab)
			msgexit("error malloc getpath.strsplit()");
	}
	return (tab);
}

char	*findcdpath(char *s, t_env **ls)
{
	char	**cd;
	char	*path;
	int		i;

	path = NULL;
	if (s[0] != '/' && !ft_strnstr(s, "./", 2) && !ft_strnstr(s, "../", 3) &&
	ft_strcmp(s, ".") && ft_strcmp(s, "..") && (cd = getpath("CDPATH", ls)))
	{
		i = -1;
		while (cd[++i])
		{
			if (cd[i][ft_strlen(cd[i]) - 1] != '/')
				cd[i] = ft_fstrjoin(cd[i], "/", 1);
			path = ft_fstrjoin(cd[i], s, 3);
			if (access(path, F_OK) != -1)
			{
				ft_freetab(cd);
				return (path);
			}
			else
				ft_memdel((void**)&path);
		}
		ft_freetab(cd);
	}
	return (path);
}

int		ft_tabcount(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			i++;
	}
	return (i);
}

char	*delonepath(char *path)
{
	int		i;
	int		j;
	char	**tab;
	char	*s;

	j = 0;
	tab = ft_strsplit(path, '/');
	j = ft_tabcount(tab) - 1;
	s = ft_strdup("/");
	if (tab && j > 0)
	{
		i = -1;
		while (tab && tab[++i] && i < j)
		{
			if (i > 0)
				s = ft_fstrjoin(s, "/", 1);
			s = ft_fstrjoin(s, tab[i], 1);
		}
		ft_freetab(tab);
		ft_memdel((void**)&path);
	}
	return (s);
}

char	*joinpath(char *dest, char *src, char *oldpwd)
{
	char	**tabpath;
	int		i;
	char	*s;

	if (ft_strcmp(src, oldpwd) == 0 || src[0] == '/')
		s = ft_strdup(src);
	else
	{
		s = ft_strdup(dest);
		tabpath = ft_strsplit(src, '/');
		i = 0;
		while (tabpath && tabpath[i])
		{
			if (ft_strcmp(tabpath[i], "..") == 0)
				s = delonepath(s);
			else if (ft_strcmp(tabpath[i], ".") != 0)
			{
				s = ft_fstrjoin(s, "/", 1);
				s = ft_fstrjoin(s, tabpath[i], 1);
			}
			i++;
		}
		ft_freetab(tabpath);
	}
	return (s);
}
