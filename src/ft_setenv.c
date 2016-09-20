#include "../inc/minishell.h"
#include <stdlib.h>

void			ft_putenv(t_env **lst)
{
	t_env *tmp;

	tmp = *lst;
	while (tmp)
	{
		ft_putstr(tmp->key);
		ft_putchar('=');
		ft_putstr(tmp->value);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void			setter_env(char **args, int n, t_env **lst)
{
	t_env	*tmp;

	tmp = findvar(args[0], lst);
	if (tmp)
	{
		tmp = (n == 2) ? updatevar(tmp->key, args[1], lst) :
		updatevar(tmp->key, "", lst);
	}
	else
	{
		if (n == 2)
			pushback(args[0], args[1], lst);
		else
			pushback(args[0], "", lst);
	}
}

int				ft_setenv(char **args, t_env **lst)
{
	int		i;
	char	**vars;

	if (args[1])
	{
		vars = ft_parsing(args[1]);
		i = 0;
		while (vars[i])
			i++;
		if (i > 2)
		{
			msgerror("setenv: too many arguments.");
			return (-1);
		}
		else
			setter_env(vars, i, lst);
		ft_freetab(vars);
	}
	else
	{
		if(*lst)
			ft_putenv(lst);
	}
	return (EXIT_SUCCESS);
}