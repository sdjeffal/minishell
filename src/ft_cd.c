#include "../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static int	ft_chdir(char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret < 0)
	{
		ret = -1;
		if (access(path, F_OK) != -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(path, 2);
			if (access(path, X_OK) != -1)
				msgerror(" is not directory");
			else
				msgerror(" no permission");
		}
		else
			msgerror("cd: no such file or directory");
	}
	else
		ret = EXIT_SUCCESS;
	return (ret);
}

static int	ft_goto(char *path, char *oldpwd, t_env **lst)
{
	t_env	*env;
	char	newcwd[PATH_MAX + 1];
	char	oldcwd[PATH_MAX + 1];
	int		ret;

	getcwd(oldcwd, PATH_MAX + 1);
	if ((ret = ft_chdir(path)) == 0)
	{
		ft_memcpy(oldpwd, oldcwd, PATH_MAX + 1);
		getcwd(newcwd, PATH_MAX + 1);
		if (!(env = updatevar("PWD", newcwd, lst)))
			pushback("PWD", newcwd, lst);
		if (!(env = updatevar("OLDPWD", oldcwd, lst)))
			pushback("OLDPWD", oldcwd, lst);
	}
	return (ret);
}

char	*initpath(char *arg, t_env **lst, char *oldpwd)
{
	char	*path;
	char	*tmp;

	path = NULL;
	if (arg[0] == '~')
	{
		tmp = ft_strsub(arg, 1, ft_strlen(arg) - 1);
		path = ft_fstrjoin(ft_gethome(lst), tmp, 2);
	}
	else if (arg[0] == '-' && arg[1] == '\0')
	{
		if (oldpwd[0] != '\0')
		{
			path = ft_strdup(oldpwd);
			ft_putendl(path);
		}
		else
			path = NULL;
	}
	else
		path = ft_strdup(arg);
	return (path);
}

int	ft_cd(char **args, t_env **lst)
{
	char	**vars;
	char	*path;
	t_env	*env;
	int		ret;
	static char	oldpwd[PATH_MAX + 1];

	ret = 0;
	if (oldpwd[0] == '\0')
	{
		if ((env = findvar("OLDPWD", lst)) && env->value)
			ft_memcpy(oldpwd, env->value, ft_strlen(env->value));
	}
	vars = ft_parsing(args[1]);
	if (vars && vars[0])
		path = initpath(vars[0], lst, oldpwd);
	else
		path = ft_strdup(ft_gethome(lst));
	if (path)
	{
		ret = ft_goto(path, oldpwd, lst);
		ft_memdel((void**)&path);
	}
	return (ret);
}
