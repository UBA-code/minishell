/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:28:56 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/01 13:50:18 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_clear(t_cmd_node **head)
{
	t_cmd_node	*current;
	int			i;
	t_cmd_node	*temp;

	i = 0;
	current = *head;
	while (current)
	{
		i = -1;
		while (++i < current->lexer_size)
			free(current->lexer[i].content);
		temp = current;
		current = current->next;
		free(temp->lexer);
		free(temp);
	}
}
