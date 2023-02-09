/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:41:54 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/09 15:45:26 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_del_node(t_mini_env **head, char *variable)
{
	t_mini_env	*current;
	t_mini_env	*temp;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->name, variable))
		{
			temp = current;
			current->previous->next = current->next;
			free(temp->name);
			free(temp->value);
			free(temp);
			return ;
		}
		current = current->next;
	}
}

void	exit_cmd(int error_code)
{
	exit(error_code);
}