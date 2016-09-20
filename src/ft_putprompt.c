#include "../inc/minishell.h"
#include <unistd.h>
#include <limits.h>

void	ft_putcwd(char *cwd, struct passwd *pw)
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

void	ft_putprompt(t_env	**lst)
{
	struct passwd	*pw;
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	pw = getpwuid(getuid());
	if (pw && pw->pw_name && cwd[0])
	{
		ft_putstr(pw->pw_name);
		ft_putstr("@:");
		ft_putcwd(cwd, pw);
	}
	else if (cwd[0])
		ft_putstr(cwd);
	else if (pw && pw->pw_name)
		ft_putstr(pw->pw_name);
	ft_putstr(PROMPT);
}
