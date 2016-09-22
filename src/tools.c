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
	if (ft_strcmp(s, "/") != 0 && (cdpath = getpath("CDPATH", lst)))
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
