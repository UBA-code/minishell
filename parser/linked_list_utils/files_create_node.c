/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:25:06 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/04 19:56:14 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	files_add_back_lst(t_files	*head, t_files *node)
{
	while (head->next)
		head = head->next;
	head->next = node;
}

t_files	*files_create_node(t_files **head, char *file, char type)
{
	t_files	*node;

	node = malloc(sizeof(t_files));
	if (!*head)
		*head = node;
	else
		files_add_back_lst(*head, node);
	node->file = file;
	node->type = type;
	node->next = 0;
	return (node);
}
