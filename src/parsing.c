/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 18:07:54 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/09/30 18:11:03 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

static char	**splitcommand(char *command, char *line)
{
	char			**arg;
	unsigned int	l;

	arg = NULL;
	if (command)
	{
		if ((arg = (char**)malloc(sizeof(char*) * 3)) != NULL)
		{
			if ((arg[0] = ft_strdup(command)) == NULL)
				msgexit("strdup(function.splitcommand();");
			l = ft_strlen(arg[0]);
			arg[1] = ft_strsub(line, l + 1, ft_strlen(line) - l);
			if (arg[1][0] == '\0')
				ft_memdel((void**)&arg[1]);
			arg[2] = 0;
		}
		else
			msgexit("malloc(function.splitcommand())");
	}
	return (arg);
}

char		*strtrimdelimit(char const *s)
{
	char	*p_start;
	char	*p_end;
	size_t	start;
	size_t	end;
	size_t	l_s;

	if (s == NULL)
		return (NULL);
	p_start = (char *)s;
	l_s = ft_strlen(s);
	p_end = (char*)s + l_s - 1;
	start = 0;
	end = 0;
	while (ISDELIM(p_start[start]))
		start++;
	if (p_start[start] == '\0')
		return (ft_strnew(0));
	while (ISDELIM(*p_end))
	{
		p_end--;
		end++;
	}
	return (ft_strsub(s, start, l_s - start - end));
}

char		**splitline(char *line)
{
	char	*tmp;
	char	**split;
	char	**arg;

	arg = NULL;
	if (line)
	{
		tmp = strtrimdelimit(line);
		if (tmp)
		{
			split = ft_strsplitshell(tmp);
			if (split && split[0])
				arg = splitcommand(split[0], tmp);
			ft_freetab(split);
			ft_memdel((void**)&tmp);
			return (arg);
		}
	}
	return (NULL);
}

char		**ft_parsing(char *line)
{
	char	**vars;
	char	*tmp;

	vars = NULL;
	tmp = strtrimdelimit(line);
	if (tmp)
	{
		vars = ft_strsplitshell(tmp);
		ft_memdel((void**)&tmp);
	}
	return (vars);
}
