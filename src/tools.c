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

char	*findcdpath(char *s, t_env **lst)
{
	char	**cdpath;
	char	*path;
	int		i;

	path = NULL;
	if (!ft_strcmp(s, "/")  && !ft_strcmp(s, ".") && !ft_strcmp(s, "..") && 
	!ft_strcmp(s, "./") && !ft_strcmp(s, "../") && (cdpath = getpath("CDPATH", lst)))
	{
		i = -1;
		while (cdpath[++i])
		{
			if (cdpath[i][ft_strlen(cdpath[i]) - 1] != '/')
				cdpath[i] = ft_fstrjoin(cdpath[i], "/", 1);
			path = ft_fstrjoin(cdpath[i], s, 3);
			if (access(path, F_OK) != -1)
			{
				ft_freetab(cdpath);
				return (path);
			}
			else
				ft_memdel((void**)&path);
		}
		ft_freetab(cdpath);
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

char *delonepath(char *path)
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

char	*joinpath(char	*dest, char *src, char *oldpwd)
{
	char	**tabpath;
	int		i;
	char	*s;

	if (ft_strcmp(src, oldpwd) == 0)
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
