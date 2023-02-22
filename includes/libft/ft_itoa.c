/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:22:48 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/23 00:01:09 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_itoa(int nbr, char *tab, int *i)
{
	if (nbr == -2147483648)
	{
		tab[++*i] = '-';
		tab[++*i] = '2';
		ft_putnbr_itoa(147483648, tab, i);
	}
	else if (nbr < 0)
	{
		tab[++*i] = '-';
		ft_putnbr_itoa(-nbr, tab, i);
	}
	else if (nbr > 9)
	{
		ft_putnbr_itoa(nbr / 10, tab, i);
		ft_putnbr_itoa(nbr % 10, tab, i);
	}
	else
		tab[++*i] = nbr + '0';
}

char	*ft_itoa(int n)
{
	int		i;
	char	*tab;

	i = -1;
	tab = malloc(13);
	if (tab == NULL)
		return (NULL);
	ft_putnbr_itoa(n, tab, &i);
	tab[++i] = '\0';
	return (tab);
}
