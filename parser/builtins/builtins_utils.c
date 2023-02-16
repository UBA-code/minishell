/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:50:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/16 18:26:57 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	modifie_variable(char *variable, char *new_value)
{
	t_mini_env	*current;

	current = g_global.env_head;
	while (current)
	{
		if (ft_strcmp(current->name, variable))
		{
			free(current->value);
			if (new_value)
				current->value = ft_strdup(new_value);
			else
				current->value = 0;
			return ;
		}
		current = current->next;
	}
}

