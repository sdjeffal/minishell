/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 16:53:38 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/09/29 16:54:53 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_exit(char *line, char **args, t_env **lst)
{
	int	i;

	i = -1;
	ft_cleanenv(lst);
	ft_memdel((void**)&line);
	while (++i < 3)
		ft_memdel((void**)&args[i]);
	ft_memdel((void**)&args);
	exit(EXIT_SUCCESS);
}

int		builtin(char **args, t_env **lst)
{
	char	*builtin_str[6];
	int		(*builtin_func[6])(char **, t_env **);
	int		i;

	i = -1;
	builtin_str[0] = "cd";
	builtin_str[1] = "echo";
	builtin_str[2] = "env";
	builtin_str[3] = "pwd";
	builtin_str[4] = "setenv";
	builtin_str[5] = "unsetenv";
	builtin_func[0] = &ft_cd;
	builtin_func[1] = &ft_echo;
	builtin_func[2] = &ft_env;
	builtin_func[3] = &ft_pwd;
	builtin_func[4] = &ft_setenv;
	builtin_func[5] = &ft_unsetenv;
	while (++i < (sizeof(builtin_str) / sizeof(char*)))
	{
		if (ft_strcmp(builtin_str[i], args[0]) == 0)
			return ((*builtin_func[i])(args, lst));
	}
	return (EXIT_FAILURE);
}
