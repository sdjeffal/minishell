/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 18:11:38 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/09/30 18:12:30 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include <stdio.h>

int				execute(char *line, char **args, t_env **lst)
{
	int		status;
	char	*str;

	status = 0;
	if (!args || args[0] == NULL)
		return (EXIT_SUCCESS);
	if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(line, args, lst);
	if ((status = builtin(args, lst)) != EXIT_FAILURE)
		return (status);
	if ((status = ft_launch(args, lst)) != EXIT_FAILURE)
		return (status);
	else
	{
		str = ft_strjoin(args[0], ": Command not found.");
		msgerror(str);
		ft_memdel((void**)&str);
		return (EXIT_FAILURE);
	}
}

static int		ft_minishell(t_env **lstenv)
{
	char	*line;
	char	**cmd;
	char	**args;
	int		status;
	int		i;

	status = 0;
	while (42)
	{
		i = -1;
		ft_putprompt(lstenv);
		get_next_line(0, &line);
		cmd = ft_strsplit(line, ';');
		while (cmd[++i])
		{
			args = splitline(cmd[i]);
			status = execute(cmd[i], args, lstenv);
			ft_freetab(args);
		}
		ft_memdel((void**)&line);
		ft_freetab(cmd);
	}
	return (status);
}

int				main(int ac, char **av, const char **environ)
{
	t_env	*begin;
	int		status;

	(void)ac;
	(void)av;
	begin = NULL;
	if (environ)
		ft_cpyenv(environ, &begin);
	status = ft_minishell(&begin);
	return (status);
}
