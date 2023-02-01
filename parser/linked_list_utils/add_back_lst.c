/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:00:39 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/01/31 18:01:44 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_back_lst(t_cmd_node **head, t_cmd_node *node)
{
	t_cmd_node	*current;

	current = *head;
	if (!current)
		*head = node;
	else
	{
		while (current->next)
			current = current->next;
		current->next = node;
		node->next = 0;
	}
}
