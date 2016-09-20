#include "../inc/minishell.h"
#include <stdlib.h>

int delvar(char *key, t_env **lst)
{
	t_env	*tmp;
	t_env	*pre;
	
	pre = *lst;
	if (!ft_strcmp(pre->key, key))
	{
		*lst = pre->next;
		freevar(&pre);
		return (1);
	}
	tmp = pre->next;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			pre->next = tmp->next;
			freevar(&tmp);
			return (1);
		}
		pre = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unsetenv(char **args, t_env **lst)
{
	char	**vars;
	int		i;

	i = -1;
	if (args[1])
	{
		vars = ft_parsing(args[1]);
		if (vars)
		{
			while (vars[++i])
				delvar(vars[i], lst);
		}
		else
		{
			msgerror("unsetenv: Too few arguments.");
			return (-1);
		}
		ft_freetab(vars);
	}
	else
	{
		msgerror("unsetenv: Too few arguments.");
		return (-1);
	}
	return (EXIT_SUCCESS);
}
