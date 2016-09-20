/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 10:44:39 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/05/26 19:17:27 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_fstrjoin(char *s1, char *s2, int i)
{
	char *tmp1;
	char *tmp2;
	char *s;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		s = ft_strdup(s2);
	else if (s2 == NULL)
		s = ft_strdup(s1);
	else
	{
		tmp1 = s1;
		tmp2 = s2;
		s = ft_strjoin(s1, s2);
		if (i == 1 || i == 0)
			ft_memdel((void**)&tmp1);
		if (i == 2 || i == 0)
			ft_memdel((void**)&tmp2);
	}
	return (s);
}
