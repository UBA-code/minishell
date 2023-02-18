/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:38:39 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/18 11:40:04 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_search(char *variable)
{
	t_mini_env *current;

	current = g_global.env_head;
	while (current)
	{
		if (ft_strcmp(current->name, variable))
			return (1);
		current = current->next;
	}
	return (0);
}

void	env_cmd(char c)
{
	t_mini_env	*current;

	current = g_global.env_head;
	if (c == 'x')
	{
		while (current)
		{
			if (current->value == 0)
				printf("declare -x %s\n", current->name);
			else
				printf("declare -x %s=\"%s\"\n", current->name, current->value);
			current = current->next;
		}
	}
	else
	{
		while (current)
		{
			if (current->value)
				printf("%s=%s\n", current->name, current->value);
			current = current->next;
		}
	}
}
