#include "../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

char	*ft_getcwd(t_env **env)
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

int		ft_pwd(char **args, t_env **lst)
{
	char	*cwd;
	
	cwd = ft_getcwd(lst);
	ft_putendl(cwd);
	return (EXIT_SUCCESS);
}
