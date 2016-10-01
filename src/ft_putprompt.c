/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putprompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 18:33:03 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/10/01 16:57:56 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

void		ft_putcwd(char *cwd, struct passwd *pw)
{
	char	*path;
	int		n;

	if (pw->pw_dir && ft_strstr(cwd, pw->pw_dir))
	{
		n = ft_strlen(pw->pw_dir);
		path = ft_strsub(cwd, n, ft_strlen(cwd) - n);
		if (!path)
			ft_putstr(cwd);
		else
		{
			ft_putchar('~');
			ft_putstr(path);
			ft_memdel((void**)&path);
		}
	}
	else
		ft_putstr(cwd);
}

static char	*ft_initpwd(t_env **lst)
{
	char	cwd[PATH_MAX + 1];
	t_env	*env_pwd;
	char	*pwd;

	pwd = NULL;
	if ((env_pwd = findvar("PWD", lst)))
		pwd = ft_strdup(env_pwd->value);
	else if (getcwd(cwd, PATH_MAX + 1))
		pwd = ft_strdup(cwd);
	return (pwd);
}

void		ft_putprompt(t_env **lst)
{
	struct passwd	*pw;
	char			*cwd;

	cwd = ft_initpwd(lst);
	pw = getpwuid(getuid());
	if (pw && pw->pw_name && cwd[0])
	{
		ft_putstr(pw->pw_name);
		ft_putstr("@:");
		ft_putcwd(cwd, pw);
		ft_memdel((void**)&cwd);
	}
	else if (cwd[0])
	{
		ft_putstr(cwd);
		ft_memdel((void**)&cwd);
	}
	else if (pw && pw->pw_name)
		ft_putstr(pw->pw_name);
	ft_putstr(PROMPT);
}
