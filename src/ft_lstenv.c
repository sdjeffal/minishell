#include "../inc/minishell.h"
#include <stdlib.h>

t_env	*newvar(char *key, char *value)
{
	t_env	*new;

	new = (t_env*)malloc(sizeof(t_env));
	if (new)
	{
		if (key)
			new->key = ft_strdup(key);
		if (value)
			new->value = ft_strdup(value);
		else
			new->value = NULL;
		new->next = NULL;
	}
	else
		msgexit("error malloc: function(newelem)");
	return(new);
}

void	pushback(char *key, char *value, t_env **begin)
{
	t_env *tmp;

	if (*begin == NULL)
		*begin = newvar(key, value);
	else 
	{
		tmp = *begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newvar(key, value);
	}
}

t_env	*findvar(char *key, t_env **begin)
{
	t_env	*tmp;

	tmp = *begin;
	if (key)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, key))
				return (tmp);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

t_env	*updatevar(char *key, char *value ,t_env **begin)
{
	t_env	*tmp;

	tmp = findvar(key, begin);
	if (tmp)
	{
		if (tmp->value)
		{
			ft_memdel((void**)&tmp->value);
			tmp->value = ft_strdup(value);
		}
		return (tmp);
	}
	return (NULL);
}

void	freevar(t_env **env)
{
	if (*env)
	{
		if ((*env)->key)
			ft_memdel((void**)&(*env)->key);
		if ((*env)->value)
			ft_memdel((void**)&(*env)->value);
		ft_memdel((void**)&(*env));
	}
}
