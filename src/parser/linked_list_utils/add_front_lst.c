/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_front_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:03:40 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/22 23:05:56 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_front_lst(t_lexer_node **head, t_lexer_node *node)
{
	t_lexer_node	*current;

	current = *head;
	if (!current)
		*head = node;
	else
	{
		node->next = current->next;
		current->next = node;
	}
}
