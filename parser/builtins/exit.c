/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:43:19 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/18 11:43:25 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_cmd(char **args)
{
	if (args[1] && !args[2])
		exit(ft_atoi(args[1]));
	else if (!args[1])
		exit(0);
	else
		ft_error("exit: too many arguments", 1);
}
