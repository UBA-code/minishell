/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:43:19 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/21 15:45:35 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_exit(char *nb)
{
	int	i;

	i = -1;
	while (nb[++i])
	{
		if (!((nb[i] >= '0' && nb[i] <= '9') || nb[i] == '+' || nb[i] == '-'))
		{
			ft_error("bash: ", 255);
			ft_error(nb, 255);
			ft_error(": numeric argument required", 255);
			return (0);
		}
	}
	if (nb[i - 1] == '+' || nb[i - 1] == '-')
	{
		ft_error("bash: ", 255);
		ft_error(nb, 255);
		ft_error(": numeric argument required", 255);
		return (0);
	}
	return (1);
}

void	exit_cmd(char **args)
{
	if (args[1] && !args[2] && check_exit(args[1]))
		exit(ft_atoi(args[1]));
	if (!args[1])
		exit(0);
	ft_error("exit: too many arguments", 1);
}
