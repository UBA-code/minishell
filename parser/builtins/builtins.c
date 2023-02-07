/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:57:56 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/07 22:07:39 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char *msg, int option)
{
	if (option)
		printf("%s", msg);
	else
		printf("%s\n", msg);
}

char	*get_variable(char *variable)
{
	t_mini_env	*current;

	current = global.env_head;
	while (current)
	{
		if (ft_strcmp(current->name, variable))
			retuurn (current->value);
		current = current->next;
	}
	return (0);
}
