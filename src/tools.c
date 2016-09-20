#include "../inc/minishell.h"

char	**getpath(char *name, t_env **env)
{
	char	**tab;
	t_env	*elem;

	tab = NULL;
	if ((elem = findvar(name, env)) && elem->value)
	{
		tab = ft_strsplit(elem->value, ':');
		if (!tab)
			msgexit("error malloc function strsplit in function getpath");
	}
	return (tab);
}
