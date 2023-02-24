/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:23:20 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/22 23:05:56 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer_node	*lexer_create_node(t_lexer_node **head)
{
	t_lexer_node	*node;

	node = malloc(sizeof(t_lexer_node));
	add_back_lst(head, node);
	return (node);
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

t_mini_env	*env_create_node(char *name, char *value)
{
	t_mini_env	*node;

	node = malloc(sizeof(t_mini_env));
	if (!g_global.env_head)
	{
		g_global.env_head = node;
		node->previous = 0;
	}
	else
		env_add_back_lst(g_global.env_head, node);
	node->name = name;
	node->value = value;
	node->next = 0;
	return (node);
}