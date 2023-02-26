/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:17:45 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/26 22:46:24 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	parser_work(t_lexer_node *node)
{
	int	i;
	int	j;

	node->cmd_struct.files_head = 0;
	j = 0;
	i = 0;
	node->cmd_struct.cmd = ft_calloc(sizeof(char *)
			, parser_get_size(node) + 1);
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
		// node->cmd_struct.cmd[j] = 0;
		i++;
	}
	// node->cmd_struct.cmd[j] = 0;
	return (1);
}

int	check_env(char *cmd, char **paths)
{
	if (!paths)
	{
		// ft_error(cmd, 127);
		// ft_error(": command not found\n", 127);
		free(cmd);
		return (0);
	}
	return (1);
}

char	*get_cmd_path(char *cmd)
{
	char	**paths;
	int		i;
	char	*final;

	i = -1;
	if (access(cmd, X_OK) == 0 || cmd == 0)
		return (cmd);
	paths = ft_split(get_variable_cmd("PATH"), ":");
	if (!check_env(cmd, paths))
		return (NULL);
	while (paths[++i])
	{
		final = ft_strjoin(ft_strdup(paths[i]), "/");
		final = ft_strjoin(final, cmd);
		if (access(final, X_OK) == 0)
		{
			tab_free(paths);
			return (free(cmd), final);
		}
		free(final);
	}
	// ft_error(cmd, 127);
	// ft_error(": command not found\n", 127);
	// free(cmd);
	return (tab_free(paths), cmd);
}

void print_lex(t_lexer_node *head)
{
	
	t_lexer_node *current = head;
	t_files *files;

	while (current)
	{
		int i = 0;
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

int	parser_utils(t_lexer_node **lexer_head)
{
	t_lexer_node	*current;
	int				i;

	current = *lexer_head;
	while (current)
	{
		if (!parser_work(current))
			return (parse_error_free(*lexer_head), 0);
		current = current->next;
	}
	i = -1;
	current = *lexer_head;
	while (current)
	{
		// if (!(current->cmd_struct.cmd[0]))
			// current->cmd_struct.cmd[0] = ft_strdup("");
		if (current->cmd_struct.cmd[0] && !is_builtin(current->cmd_struct.cmd[0]))
			current->cmd_struct.cmd[0] = get_cmd_path(current->cmd_struct.cmd[0]);
		current = current->next;
	}
	// print_lex(*lexer_head);
	return (1);
}
// ==============================================

