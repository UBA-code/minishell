/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:49:25 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/21 12:16:23 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_parser(t_lexer_node *head)
{
	int		i;
	t_files	*files_head;
	t_files	*temp;

	while (head)
	{
		i = 0;
		while (head->cmd_struct.cmd[i])
		{
			free(head->cmd_struct.cmd[i]);
			i++;
		}
		free(head->cmd_struct.cmd);
		files_head = head->cmd_struct.files_head;
		while (files_head)
		{
			free(files_head->file);
			temp = files_head;
			files_head = files_head->next;
			free(temp);
		}
		head = head->next;
	}
}

void	skip_files(t_lexer_node *node, int *i)
{
	while (*i < node->lexer_size)
	{
		if (node->lexer[*i].type == '\'' || node->lexer[*i].type == '"'
			|| node->lexer[*i].type == 'W')
			break ;
		++(*i);
	}
}

int	parser_get_size(t_lexer_node *node)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < node->lexer_size)
	{
		if (node->lexer[i].type == '>' || node->lexer[i].type == '<')
			skip_files(node, &i);
		else if ((node->lexer[i].type == '\'' || node->lexer[i].type == '"'
				|| node->lexer[i].type == 'W'))
			size++;
		i++;
	}
	return (size);
}

char	get_file_type(t_lexer_node *node, int i)
{
	if (i + 1 < node->lexer_size && node->lexer[i].type == '>'
		&& node->lexer[i + 1].type != '>' && node->lexer[i + 2].type != '>'
		&& node->lexer[i + 2].type != '<' && node->lexer[i + 1].type != '<')
		return ('O');
	if (i + 1 < node->lexer_size && node->lexer[i].type == '>'
		&& node->lexer[i + 1].type == '>' && node->lexer[i + 2].type != '>'
		&& node->lexer[i + 2].type != '<')
		return ('A');
	if (i + 1 < node->lexer_size && node->lexer[i].type == '<'
		&& node->lexer[i + 1].type != '<' && node->lexer[i + 2].type != '>'
		&& node->lexer[i + 2].type != '<' && node->lexer[i + 1].type != '>')
		return ('I');
	if (i + 1 < node->lexer_size && node->lexer[i].type == '<'
		&& node->lexer[i + 1].type == '<' && node->lexer[i + 2].type != '>'
		&& node->lexer[i + 2].type != '<')
		return ('H');
	return (0);
}

int	get_after_file(t_lexer_node *node, int i)
{
	char	type;

	type = get_file_type(node, i);
	if (!type)
		return (0);
	while (i < node->lexer_size)
	{
		if ((node->lexer[i].type == '\'' || node->lexer[i].type == '"'
				|| node->lexer[i].type == 'W'))
		{
			files_create_node(&(node->cmd_struct.files_head),
				join_string(node, &i), type);
			return (i);
		}
		i++;
	}
	return (-1);
}
