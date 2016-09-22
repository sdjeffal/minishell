#include "../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static char	**ft_parse_launch(char *line)
{
	char **arg;
	char *tmp;

	arg = NULL;
	if (line)
	{
		tmp = strtrimdelimit(line);
		if (tmp)
		{
			arg = ft_strsplitshell(tmp);
			ft_memdel((void**)&tmp);
		}
	}
	return (arg);
}

char	*ft_findpath(char *cmd, t_env **lst)
{
	char	*path;
	char	**tmp;
	int		i;

	i = 0;
	path = NULL;
	tmp = getpath("PATH", lst);
	while (tmp && tmp[i])
	{
		if (tmp[i][ft_strlen(tmp[i]) - 1] != '/')
			tmp[i] = ft_fstrjoin(tmp[i], "/", 1);
		tmp[i] = ft_fstrjoin(tmp[i], cmd, 1);
		if (access(tmp[i], F_OK) != -1)
		{
			path = ft_strdup(tmp[i]);
			ft_freetab(tmp);
			return (path);
		}
		i++;
	}
	ft_freetab(tmp);
	if (ft_strnstr(cmd, "./", 2))
		return (path = ft_strdup(cmd));
	return (path);
}

int		ft_exec(char *cmd, char **args, char **env)
{
	int   status;
	pid_t pid_p;

	if (access(cmd, F_OK) != -1)
	{
		if (access(cmd, X_OK) == -1)
			msgerror("no permission");
		else
		{
			pid_p = fork();
			if (pid_p == 0)
			{
				if (execve(cmd, args, env) == -1)
					msgexit("not executable file");
			}
			else if (pid_p < 0)
				msgexit("error memory fork: file:ft_launch -> function ft_exec");
			else
				wait(&status);
		}
	}
	else
		return (EXIT_FAILURE);
	return (status);
}

int	ft_launch(char **args, t_env **lst)
{
	char **arg;
	char **envp;
	char *cmd;
	char *tmp;
	char *tmp2;
	int status;

	cmd = ft_findpath(args[0], lst);
	if (cmd)
	{
		tmp = ft_fstrjoin(cmd, " ", 3);
		tmp2 = ft_fstrjoin(tmp, args[1], 3);
		arg = ft_parse_launch(tmp2);
			envp = envtotab(lst);
		status = ft_exec(cmd, arg, envp);
		ft_memdel((void**)&cmd);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&tmp2);
		ft_freetab(arg);
		ft_freetab(envp);
	}
	else
		status = EXIT_FAILURE;
	return (status);
}
