/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:17:45 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/19 11:39:44 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	free_parser(t_lexer_node *head)
{
	int		i;
	t_files	*files_head;
	t_files	*temp;

	files_head = head->cmd_struct.files_head;
	while (head)
	{
		i = 0;
		while (head->cmd_struct.cmd[i])
		{
			free(head->cmd_struct.cmd[i]);
			i++;
		}
		free(head->cmd_struct.cmd);
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
	return (0);
}

int	parser_work(t_lexer_node *node)
{
	int	i;
	int	j;

	node->cmd_struct.files_head = 0;
	j = 0;
	i = 0;
	node->cmd_struct.cmd = malloc(sizeof(char *) * (parser_get_size(node) + 1));
	while (i < node->lexer_size)
	{
		if (node->lexer[i].type == '<' || node->lexer[i].type == '>')
		{
			i = get_after_file(node, i);
			if (i == 0)
				return (0);
		}
		else if (node->lexer[i].type == '\'' || node->lexer[i].type == '"'
				|| node->lexer[i].type == 'W')
			node->cmd_struct.cmd[j++] = join_string(node, &i);
		if (j && !(node->cmd_struct.cmd[j - 1]))
			j--;
		node->cmd_struct.cmd[j] = 0;
		i++;
	}
	return (1);
}

char	*get_cmd_path(char *cmd)
{
	char	**paths;
	int		i;
	char	*final;

	i = -1;
	paths = ft_split(get_variable_cmd("PATH"), ":");
	if (access(cmd, X_OK) == 0)
		return (tab_free(paths), cmd);
	while (paths[++i])
	{
		final = ft_strjoin(ft_strdup(paths[i]), "/");
		final = ft_strjoin(final, cmd);
		if (access(final, X_OK) == 0)
		{
			tab_free(paths);
			free(cmd);
			return (final);
		}
		free(final);
	}
	ft_error(cmd, 127);
	ft_error(": command not found\n", 127);
	free(cmd);
	tab_free(paths);
	return (0);
}

void	parser_utils(t_lexer_node **lexer_head)
{
	t_lexer_node	*current;
	int				i;
	int				j;

	current = *lexer_head;
	while (current)
	{
		if (!parser_work(current))
		{
			ft_error("Error, Parse Error\n", 258);
			return ;
		}
		current = current->next;
	}
	i = 0;
	current = *lexer_head;
	while (current)
	{
		current->cmd_struct.cmd[0] = get_cmd_path(current->cmd_struct.cmd[0]);
		current = current->next;
	}



	
// ------------------------------------------------------------------------









	// print
	
	current = *lexer_head;
	t_files *files;

	while (current)
	{
		i = 0;
		while (current->cmd_struct.cmd[i])
		{
			printf("%d|%s|\n", i + 1, current->cmd_struct.cmd[i]);
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
