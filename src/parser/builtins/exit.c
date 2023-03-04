/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:43:19 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/04 03:25:58 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exit_error(char *str)
{
	ft_error("minishell: ", 255);
	ft_error(str, 255);
	ft_error(": numeric argument required\n", 255);
}

int	check_exit(char *nb)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (nb[++i])
		if (nb[i] == '-' || nb[i] == '+')
			j++;
	if (j > 1)
		return (exit_error(nb), 0);
	i = -1;
	while (nb[++i])
		if (!((nb[i] >= '0' && nb[i] <= '9') || nb[i] == '+' || nb[i] == '-'))
			return (exit_error(nb), 0);
	if (nb[i - 1] == '+' || nb[i - 1] == '-')
		return (exit_error(nb), 0);
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
