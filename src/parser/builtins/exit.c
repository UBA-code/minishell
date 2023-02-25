/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:43:19 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/25 11:20:56 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
			ft_error(": numeric argument required\n", 255);
			return (0);
		}
	}
	if (nb[i - 1] == '+' || nb[i - 1] == '-')
	{
		ft_error("bash: ", 255);
		ft_error(nb, 255);
		ft_error(": numeric argument required\n", 255);
		return (0);
	}
	return (1);
}

void	exit_cmd(char **args)
{
	if (args[1] && !check_exit(args[1]))
		exit(255);
	if (args[1] && !args[2])
	{
		printf("exit\n");
		exit(ft_atoi(args[1]));
	}
	if (!args[1])
	{
		printf("exit\n");
		exit(0);
	}
	else
		ft_error("exit: too many arguments\n", 1);
}
