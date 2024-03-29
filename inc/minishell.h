/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 16:49:31 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/10/01 16:52:56 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>

# define ISDELIM(c)((c == ' ' || c == '\t' || c == '\r') ? 1 : 0)

# define PROMPT "$>"

typedef struct stat		t_stat;
typedef struct			s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}						t_env;

int						execute(char *line, char **args, t_env **lst);
t_env					*newvar(char *key, char *value);
void					pushback(char *key, char *value, t_env **begin);
t_env					*findvar(char *key, t_env **begin);
t_env					*updatevar(char *key, char *value, t_env **begin);
void					freevar(t_env **env);
int						ft_cpyenv(const char **environ, t_env **begin);
char					**splitenv(const char *str);
t_env					*ft_cpylst(t_env **src);
void					ft_cleanenv(t_env **lst);
void					modifyenv(char *var, t_env **lst);
void					ft_getcwd(char *cwd, int len, t_env **lst);
void					ft_putprompt(t_env	**lst);
char					**ft_parsing(char *line);
char					**splitline(char *line);
char					*strtrimdelimit(char const *s);
int						ft_echo(char **args, t_env **lst);
int						ft_setenv(char **args, t_env **lst);
int						ft_unsetenv(char **args, t_env **lst);
int						ft_pwd(char **args, t_env **lst);
int						ft_cd(char **args, t_env **lst);
int						ft_env(char **args, t_env **lst);
int						builtin(char **args, t_env **lst);
void					ft_exit(char *line, char **args, t_env **lst);
void					putbackslash(char *str, char *option);
int						ft_launch(char **args, t_env **lst);
void					msgerropt(char c);
void					msgexit(const char *s);
void					msgerror(const char *s);
void					setter_env(char **args, int n, t_env **lst);
void					ft_putenv(t_env **lst);
int						delvar(char *key, t_env **lst);
char					**ft_strsplitshell(char const *s);
char					istypefile(char *pathfile);
char					*replacevar(char *str, t_env **lst);
char					**ft_freetab(char **tab);
char					**envtotab(t_env **env);
char					*ft_gethome(t_env **env);
char					**getpath(char *name, t_env **env);
char					*findcdpath(char *s, t_env **ls);
int						ft_tabcount(char **tab);
char					*joinpath(char	*dest, char *src, char *oldpwd);
char					*delonepath(char *path);

#endif
