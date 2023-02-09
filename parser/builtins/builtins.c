/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:57:56 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/09 15:20:09 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_cmd(char *msg, int option)
{
	if (option)
		printf("%s", msg);
	else
		printf("%s\n", msg);
}

char	*get_variable_cmd(char *variable)
{
	t_mini_env	*current;

	current = global.env_head;
	while (current)
	{
		if (ft_strcmp(current->name, variable))
			return (current->value);
		current = current->next;
	}
	return (0);
}

t_mini_env *export_cmd(t_mini_env **head, char *name, char *value)
{
	t_mini_env	*node;

	node = env_create_node(head, name, value);
	node->next = 0;
	return (node);
}

void	unset_cmd(t_mini_env **head, char *variable)
{
	env_del_node(head, variable);
}

void	env_cmd(t_mini_env *head)
{
	while (head)
	{
		printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
}