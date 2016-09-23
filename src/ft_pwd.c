#include "../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

/**
static char	*ft_getcwd(t_env **env)
{
	t_env			*home;
	char			*cwd;
	char			buff[PATH_MAX + 1];

	if (env && (home = findvar("PWD", env)))
		return (home->value);
	else
	{
		cwd = getcwd(buff, PATH_MAX + 1);
		if (cwd)
			return (cwd);
	}
	return (NULL);
}
**/
void	ft_getcwd(char *cwd, int len, t_env **lst)
{
	t_env	*env;

	ft_bzero(cwd, len);
	if ((env = findvar("PWD", lst)) && env->value)
		ft_memcpy(cwd, env->value, ft_strlen(env->value));
	else
		getcwd(cwd, len);
}

int			ft_pwd(char **args, t_env **lst)
{
	char	cwd[PATH_MAX + 1];
	
	ft_getcwd(cwd, PATH_MAX + 1, lst);
	ft_putendl(cwd);
	return (EXIT_SUCCESS);
}
