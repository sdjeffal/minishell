#include "../inc/minishell.h"
#include <stdlib.h>
#include <stdio.h>

int		execute(char *line, char **args, t_env **lst)
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
	char	**args;
	int		status;
	int		i;

	status = 0;
	while (42)
	{
		//ft_putprompt(lstenv);
		ft_putstr(PROMPT);
		get_next_line(0, &line);
		args = splitline(line);
		status = execute(line, args, lstenv);
		ft_putnendl(status);
		ft_memdel((void**)&line);
		ft_freetab(args);
	}
	return (status);;
}

int	main(int ac, char **av, const char **environ)
{
	t_env 	*begin;
	int		status;

	(void)ac;
	(void)av;
	begin = NULL;
	if (environ)
		ft_cpyenv(environ, &begin);
	status = ft_minishell(&begin);
	return (status);
}

