/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharhex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 17:42:48 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/09/29 17:44:51 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putcharhex(char *str)
{
	int		n;
	int		v;
	int		i;
	char	val[3];

	n = 0;
	i = 0;
	v = 0;
	bzero(val, 3);
	while (str[n] && ft_ishex(str[n]) && n < 2)
	{
		val[n] = str[n];
		n++;
	}
	while (--n >= 0)
		v += ft_hextodec(val[i++], n);
	if (v == 0)
		ft_putchar(' ');
	else
		ft_putchar(v);
	return (i);
}
