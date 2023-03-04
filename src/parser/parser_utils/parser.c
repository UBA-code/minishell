/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:17:45 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/04 22:14:52 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	parser_work(t_lexer_node *node)
{
	int	i;
	int	j;

	node->cmd_struct.files_head = 0;
	j = 0;
	i = -1;
	node->cmd_struct.cmd = ft_calloc(sizeof(char *),
			parser_get_size(node) + 1);
	while (++i < node->lexer_size)
	{
		if (node->lexer[i].type == '<' || node->lexer[i].type == '>')
		{
			i = get_after_file(node, i);
			if (i <= 0)
				return (0);
		}
		else if (node->lexer[i].type == '\'' || node->lexer[i].type == '"'
			|| node->lexer[i].type == 'W')
			node->cmd_struct.cmd[j++] = join_string(node, &i, 1);
		if (j && !(node->cmd_struct.cmd[j - 1]))
			j--;
		if (g_global.done)
			return (1);
	}
	return (1);
}

int	check_env(char *cmd, char **paths)
{
	if (!paths)
	{
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
	if (!cmd || *cmd == '/' || *cmd == '.')
		return (cmd);
	paths = ft_split(get_variable_cmd("PATH"), ":");
	if (!paths || !check_env(cmd, paths) || !ft_strlen(cmd))
		return (cmd);
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
	return (tab_free(paths), cmd);
}

void	print_lex(t_lexer_node *head)
{
	t_lexer_node	*current;
	t_files			*files;
	int				i;

	current = head;
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

int	parser_utils(t_lexer_node **lexer_head)
{
	t_lexer_node	*current;
	int				i;

	current = *lexer_head;
	while (current)
	{
		if (!parser_work(current) || g_global.done)
			return (parse_free(*lexer_head), 0);
		current = current->next;
		g_global.error = 0;
	}
	i = -1;
	current = *lexer_head;
	while (current)
	{
		if (current->cmd_struct.cmd[0]
			&& !is_builtin(current->cmd_struct.cmd[0]))
			*current->cmd_struct.cmd = get_cmd_path(*current->cmd_struct.cmd);
		current = current->next;
	}
	// print_lex(*lexer_head);
	return (1);
}
