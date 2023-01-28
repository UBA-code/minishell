/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:46:18 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/28 12:52:08 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

int	main(int ac, char const **av)
{
	char *s;

	while (1)
	{
		ft_putstr("1337@UBA-shell~> ");
		s = get_next_line(1);
	}
	return 0;
}
