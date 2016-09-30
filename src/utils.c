/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 18:06:20 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/09/30 18:07:44 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>

char		**ft_freetab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			ft_memdel((void**)&tab[i]);
		ft_memdel((void**)&tab);
	}
	return (tab);
}

char		*replacevar(char *str, t_env **lst)
{
	t_env	*e;
	char	*s;

	s = NULL;
	if (str[0] && str[0] == '~' && (str[1] == '/' || str[1] == '\0'))
	{
		e = findvar("HOME", lst);
		if (e && e->value)
		{
			s = ft_strjoin(e->value, &str[1]);
			ft_memdel((void**)&str);
			return (s);
		}
	}
	else if (str[0] && str[0] == '$' && ft_isprint(str[1]))
	{
		e = findvar(&str[1], lst);
		if (e && e->value)
		{
			s = ft_strdup(e->value);
			ft_memdel((void**)&str);
			return (s);
		}
	}
	return (str);
}

static int	getnbvars(t_env **lst)
{
	t_env	*tmp;
	int		i;

	if (*lst == NULL)
		return (0);
	i = 1;
	tmp = *lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char		**envtotab(t_env **env)
{
	t_env	*tmp;
	char	**tab;
	int		i;

	i = getnbvars(env);
	if (!(tab = (char**)malloc(sizeof(char*) * (i + 1))))
		msgexit("error malloc function: envtotab");
	i = 0;
	tmp = *env;
	while (tmp)
	{
		if ((tab[i] = ft_strjoin(tmp->key, "=")) == NULL)
			msgexit("error malloc function: envtotab()->ft_strjoin()");
		if (tmp->value)
		{
			if ((tab[i] = ft_fstrjoin(tab[i], tmp->value, 1)) == NULL)
				msgexit("error malloc function: envtotab()->ft_strjoin()");
		}
		i++;
		tmp = tmp->next;
	}
	tab[i] = 0;
	return (tab);
}

char		*ft_gethome(t_env **env)
{
	struct passwd	*pw;
	t_env			*home;

	if (env && (home = findvar("HOME", env)))
		return (home->value);
	else
	{
		pw = getpwuid(getuid());
		if (pw && pw->pw_dir)
			return (pw->pw_dir);
	}
	return (NULL);
}
