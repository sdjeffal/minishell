/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 16:55:23 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/10/01 15:16:36 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

char	**splitenv(const char *str)
{
	char	**env;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	env = (char**)malloc(sizeof(char*) * 3);
	if (!env)
		msgexit("error malloc: function(splitenv)");
	env[0] = ft_strsub(str, 0, i);
	if (!env[0])
		msgexit("error malloc: function(splitenv)");
	if (str[i] == '=' && str[i + 1])
	{
		env[1] = ft_strsub(str, i + 1, ft_strlen(str) - i);
		if (!env[1])
			msgexit("error malloc: function(splitenv)");
	}
	else
		env[1] = 0;
	env[2] = 0;
	return (env);
}

int		ft_cpyenv(const char **environ, t_env **begin)
{
	int		i;
	char	**tmp;

	i = 0;
	while (environ[i])
	{
		tmp = splitenv(environ[i++]);
		if (tmp && tmp[0])
		{
			if (tmp[1])
				pushback(tmp[0], tmp[1], begin);
			else
				pushback(tmp[0], "\0", begin);
			ft_memdel((void**)&tmp[0]);
			if (tmp[1])
				ft_memdel((void**)&tmp[1]);
			ft_memdel((void**)&tmp);
		}
	}
	return (1);
}

t_env	*ft_cpylst(t_env **src)
{
	t_env *tmp;
	t_env *dest;

	dest = NULL;
	tmp = *src;
	if (tmp)
	{
		while (tmp)
		{
			pushback(tmp->key, tmp->value, &dest);
			tmp = tmp->next;
		}
	}
	else
		return (NULL);
	return (dest);
}

void	ft_cleanenv(t_env **lst)
{
	t_env	*tmp;
	t_env	*next;

	if (*lst)
	{
		tmp = *lst;
		while (tmp)
		{
			next = tmp->next;
			freevar(&tmp);
			tmp = next;
		}
		*lst = NULL;
	}
}

void	modifyenv(char *var, t_env **lst)
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
