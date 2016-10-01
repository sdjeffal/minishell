/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 18:32:38 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/10/01 16:59:38 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

void	ft_getcwd(char *cwd, int len, t_env **lst)
{
	t_env	*env;

	ft_bzero(cwd, len);
	if ((env = findvar("PWD", lst)) && env->value)
		ft_memcpy(cwd, env->value, ft_strlen(env->value));
	else
		getcwd(cwd, len);
}

int		ft_pwd(char **args, t_env **lst)
{
	char	cwd[PATH_MAX + 1];

	ft_getcwd(cwd, PATH_MAX + 1, lst);
	ft_putendl(cwd);
	return (EXIT_SUCCESS);
}
