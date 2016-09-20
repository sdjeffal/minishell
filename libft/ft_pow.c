/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdjeffal <sdjeffal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 01:27:49 by sdjeffal          #+#    #+#             */
/*   Updated: 2016/03/06 04:15:07 by sdjeffal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow(int nb, int power)
{
	long int lnb;

	lnb = nb;
	if ((nb == 0) || (power < 0))
		return (0);
	else if (power == 0)
		return (1);
	else
	{
		lnb *= ft_pow(lnb, power - 1);
		if (lnb > 2147483647)
			return (0);
		else
		{
			nb = lnb;
			return (nb);
		}
	}
}
