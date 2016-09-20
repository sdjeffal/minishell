/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextodec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 01:27:49 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/03/06 04:15:07 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hextodec(char c, int ex)
{
	int nbr;

	nbr = 0;
	if (c >= 48 && c <= 57)
		nbr = (c - 48) * ft_pow(16, ex);
	else if (c >= 65 && c <= 70)
		nbr = (c - 55) * ft_pow(16, ex);
	else if (c >= 97 && c <= 102)
		nbr = (c - 87) * ft_pow(16, ex);
	return (nbr);
}
