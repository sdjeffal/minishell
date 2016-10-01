/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 18:14:18 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/10/01 04:49:32 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

static int	get_opt(char **args, char *opt)
{
	int	i;
	int	j;

	if (args)
	{
		i = 0;
		while (args[i] && args[i][0] == '-')
		{
			j = -1;
			while (args[i][++j] == '-' || args[i][j] == 'i')
				opt[0] = args[i][j];
			if (args[i][j] != '\0')
			{
				ft_putstr_fd("env: illegal option -- ", 2);
				ft_putchar_fd(args[i][j], 2);
				ft_putchar_fd('\n', 2);
				msgerror("usage: [-i] [name=value] [utility[argument ...]]");
				return (-1);
			}
			i++;
		}
	}
	return (0);
}

static void	modifyenv(char *var, t_env **lst)
{
	int		i;
	char	*s;
	char	*tmp[2];

	ft_bzero(tmp, 2);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (i)
	{
		tmp[0] = ft_strsub(var, 0, i);
		s = ft_strchr(var, '=');
		tmp[1] = ft_strdup(++s);
	}
	if (tmp[0] && tmp[1])
		setter_env(tmp, 2, lst);
	else
		setter_env(tmp, 1, lst);
	free(tmp[0]);
	free(tmp[1]);
}

static char	**ft_realloc_rest(char **args)
{
	char	**tab;
	int		i;

	tab = NULL;
	i = 0;
	while (args[i])
		i++;
	if (i)
	{
		if ((tab = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
			msgexit("error malloc function ft_realloc_rest");
	}
	i = 0;
	while (args[i])
	{
		tab[i] = ft_strdup(args[i]);
		i++;
	}
	tab[i] = 0;
	return (tab);
}

static int	parsevar(char **args, t_env **lst, char ***newargs)
{
	int		i;

	if (args)
	{
		i = 0;
		while (args[i] && args[i][0] == '-')
			i++;
		while (args[i] && ft_strchr(args[i], '='))
		{
			if (args[i][0] == '=')
			{
				msgerror("env: setenv =: Invalid argument");
				return (-1);
			}
			modifyenv(args[i], lst);
			i++;
		}
		if (args[i])
			*newargs = ft_realloc_rest(&args[i]);
	}
	return (0);
}

int			ft_envcore(char **args, char opt[2], t_env **lst)
{
	char	**argv;
	t_env	*bak;
	int		status;
	
	argv = NULL;
	bak = ft_cpylst(lst);
	if (*opt)
		ft_cleanenv(&bak);
	if (parsevar(args, &bak, &argv) == -1)
		return (-1);
	if (!argv)
		ft_putenv(&bak);
	else
	{
		status = execute(NULL, argv, &bak);
		ft_freetab(argv);
	}
	ft_cleanenv(&bak);
	return (status);
}


int			ft_env(char **args, t_env **lst)
{
	char	**tmp;
	char	opt[2];
	int 	status;

	tmp = NULL;
	ft_bzero(opt, 2);
	status = EXIT_SUCCESS;
	if (!args[1])
		ft_putenv(lst);
	else
	{
		tmp = ft_parsing(args[1]);
		if (get_opt(tmp, opt) == -1)
			return (-1);
		if ((status = ft_envcore(tmp, opt, lst)) == -1)
			return (-1);
	}
	ft_freetab(tmp);
	return (status);
}
