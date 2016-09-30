/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 16:44:17 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/09/30 18:13:34 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

void	msgerropt(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\nusage: ft_ls [-alrRtfF] [file..]", 2);
	exit(EXIT_FAILURE);
}

void	msgerror(const char *s)
{
	ft_putendl_fd(s, 2);
}

void	msgexit(const char *s)
{
	ft_putstr_fd("minishell: ", 2);
	msgerror(s);
	exit(EXIT_FAILURE);
}
