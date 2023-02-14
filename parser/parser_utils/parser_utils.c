/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:17:45 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/14 10:26:33 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	free_parser(t_lexer_node *head)
{
	int	i;

	while (head)
	{
		i = 0;
		while (head->cmd_struct.cmd[i])
		{
			free(head->cmd_struct.cmd[i]);
			i++;
		}
		free(head->cmd_struct.cmd);
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
			|| node->lexer[i].type == 'W') || node->lexer[i].type == '$')
			size++;
		i++;
	}
	return (size);
}

char	get_file_type(t_lexer_node *node, int i)
{
	if (i + 1 < node->lexer_size && node->lexer[i].type == '>'
		&& node->lexer[i + 1].type != '>')
		return ('O');
	if (i + 1 < node->lexer_size && node->lexer[i].type == '>'
		&& node->lexer[i + 1].type == '>')
		return ('A');
	if (i + 1 < node->lexer_size && node->lexer[i].type == '<'
		&& node->lexer[i + 1].type != '<')
		return ('I');
	if (i + 1 < node->lexer_size && node->lexer[i].type == '<'
		&& node->lexer[i + 1].type == '<')
		return ('H');
	return (0);
}

int	get_after_file(t_lexer_node *node, int i)
{
	char	type;

	type = get_file_type(node, i);
	while (i < node->lexer_size)
	{
		if ((node->lexer[i].type == '\'' || node->lexer[i].type == '"'
			|| node->lexer[i].type == 'W'))
		{
			files_create_node(&(node->cmd_struct.files_head),
				node->lexer[i].content, type);
			return (i);
		}
		i++;
	}
	return (0);
}

int	parser_work(t_lexer_node *node)
{
	int	i;
	int	j;

	node->cmd_struct.files_head = 0;
	j = 0;
	i = 0;
	node->cmd_struct.cmd = malloc(sizeof(char *) * parser_get_size(node) + 1);
	while (i < node->lexer_size)
	{
		if (node->lexer[i].type == '<' || node->lexer[i].type == '>')
		{
			i = get_after_file(node, i);
			if (i == 0)
				return (0);
		}
		else if (node->lexer[i].type == '\'' || node->lexer[i].type == '"')
			node->cmd_struct.cmd[j++] = join_string(node, &i);
		else if (node->lexer[i].type == 'W')
			node->cmd_struct.cmd[j++] = ft_strdup(node->lexer[i].content);
		else if (node->lexer[i].type == '$')
			node->cmd_struct.cmd[j++] = smart_get_variable(node->lexer[i].content + 1);
		if (!(node->cmd_struct.cmd[j - 1]))
			j--;
		i++;
	}
	node->cmd_struct.cmd[j] = 0;
	return (1);
}

void	parser_utils(t_lexer_node **lexer_head)
{
	t_lexer_node	*current;

	current = *lexer_head;
	while (current)
	{
		if (!parser_work(current))
		{
			ft_error("Error, Parse Error\n", 2);
			return ;
		}
		current = current->next;
	}


// ------------------------------------------------------------------------









	// print
	
	current = *lexer_head;
	t_files *files;
	files = (*lexer_head)->cmd_struct.files_head;
	int	i;
	while (current)
	{
		i = 0;
		while (current->cmd_struct.cmd[i])
		{
			printf("|%s|\n", current->cmd_struct.cmd[i]);
			i++;
		}
		files = current->cmd_struct.files_head;
		while (files)
		{
			printf("file : %s \ttype : %c\n", files->file, files->type);
			files = files->next;
		}
		current = current->next;
	}
}
