#include "../inc/minishell.h"
#include <stdlib.h>

static void	ft_updateoption(char *opt, char *line)
{
	char	*option;
	int		i;

	i = 1;
	option = "neE";
	while (line[i] != '\0' && ft_strchr(option, line[i]))
	{
		if (line[i] == option[0])
			opt[0] = 'n';
		else if (line[i] == option[1])
			opt[1] = 'e';
		else if (line[i] == option[2])
			opt[1] = 'E';
		i++;
	}
}

static int	ft_getoption(char **args, char *opt)
{
	char	*option;
	int		i;
	int		j;

	option = "neE";
	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '-' && ft_strchr(option, args[i][1]))
		{
			j = 1;
			while (args[i][j] != '\0' && ft_strchr(option, args[i][j]))
				j++;
			if (args[i][j] != '\0')
				break;
			else
				ft_updateoption(opt, args[i]);
		}
		else
			break;
	}
	return (i);
}

static void		ft_parseparams(char **ar, char *opt, char **param, t_env **lst)
{
	char	*option;
	int		i;

	i = ft_getoption(ar, opt);
	*param = ft_strnew(0);
	while (ar[i])
	{
		ar[i] = replacevar(ar[i], lst);
		*param = ft_fstrjoin(*param, ar[i], 1);
		if (*param == NULL)
			msgexit("error malloc : function ft_parseparams");
		if (ar[i + 1])
		{
			*param = ft_fstrjoin(*param, " ", 1);
			if (*param == NULL)
				msgexit("error malloc : function ft_parseparams");
		}
		i++;
	}
}

static char		**ft_parsing_echo(char *line, int *status, t_env **lst)
{
	char	**args;
	char	*tmp;
	char	opt[3];
	int		i;

	ft_bzero(opt, 3); 
	ft_memset(opt, '-', 2); 
	tmp = strtrimdelimit(line);
	if (tmp)
	{
		*status = ft_strsplitecho(&args, tmp);
		ft_memdel((void**)&tmp);
		ft_parseparams(args, opt, &tmp, lst);
		args = ft_freetab(args);
		if ((args = (char**)ft_memalloc(sizeof(char *) * 3)) ==	NULL)
			msgexit("error malloc : function ft_parsing_echo");
		args[0] = ft_strdup(opt);
		args[1] = tmp;
	}
	else
		msgexit("error malloc : function ft_parsing_echo");
	return (args);
}

int	ft_echo(char **args, t_env **lst)
{
	char	**vars;
	int		i;
	int		status;

	if (args[1])
	{
		vars = ft_parsing_echo(args[1], &status, lst);
		if (status == -1)
		{
			msgerror("Unmatched quote");
			return (-1);
		}
		if (vars)
		{
			if (vars[0][1] == 'e')
				putbackslash(vars[1], vars[0]);
			else if (vars[0][0] == 'n')
				ft_putstr(vars[1]);
			else
				ft_putendl(vars[1]);
		}
		ft_freetab(vars);
	}
	else
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}
