/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:17:45 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/05 22:33:57 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser_get_size(t_lexer_node *node)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i < node->lexer_size)
	{
		if (node->lexer[i].type == '>' || node->lexer[i].type == '<')
		{
			i += 2;
			break;
		}
		if (node->lexer[i].type == 'w')
			size++;
		i++;
	}
	return (size);
}

int	loop_get_file(t_lexer_node *node, int i)
{
	while (i < node->lexer_size)
	{
		if (node->lexer[i].type == 'w')
			return (i);
		i++;
	}
	return (0);
}

void	redirection_work(t_lexer_node *node, int *nb)
{
	int	i;

	i = 0;
	while (i < node->lexer_size)
	{
		if (node->lexer[i].type == '>' && node->lexer[i + 1].type != '>')
		{
			i = loop_get_file(node, i);	
			if (i == 0)
			{
				ft_error("Error, no output file\n", 2);	//need Check here if i == 0 means error no file
				return ;
			}
			files_create_node(&(node->cmd_struct.files_head), node->lexer[i].content, 'O');
		}
		else if (node->lexer[i].type == '>' && node->lexer[i + 1].type == '>')
		{
			i = loop_get_file(node, i);			//need Check here if i == 0 means error no file
			if (i == 0)
			{
				ft_error("Error, no output file\n", 2);	//need Check here if i == 0 means error no file
				return ;
			}
			files_create_node(&(node->cmd_struct.files_head), node->lexer[i].content, 'A');
		}
		else if (node->lexer[i].type == '<' && node->lexer[i + 1].type != '<')
		{
			i = loop_get_file(node, i);			//need Check here if i == 0 means error no file
			if (i == 0)
			{
				ft_error("Error, no output file\n", 2);	//need Check here if i == 0 means error no file
				return ;
			}
			files_create_node(&(node->cmd_struct.files_head), node->lexer[i].content, 'I');
		}
		else if (node->lexer[i].type == '<' && node->lexer[i + 1].type == '<')
		{
			i = loop_get_file(node, i);			//need Check here if i == 0 means error no file
			if (i == 0)
			{
				ft_error("Error, no output file\n", 2);	//need Check here if i == 0 means error no file
				return ;
			}
			files_create_node(&(node->cmd_struct.files_head), node->lexer[i].content, 'H');
		}
		i++;
	}
	++*nb;
}

void	parser_work(t_lexer_node *node)
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
			redirection_work(node, &i);
		if (node->lexer[i].type == 'w')
			node->cmd_struct.cmd[j++] = node->lexer[i].content;
		i++;
	}
	node->cmd_struct.cmd[j] = 0;
	// redirection_work(node);
}

void	parser_utils(t_lexer_node **lexer_head)
{
	t_lexer_node	*current;

	current = *lexer_head;
	while (current)
	{
		parser_work(current);
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
			printf("%s\n", current->cmd_struct.cmd[i]);
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
