/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:17:45 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/23 00:37:39 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (access(cmd, X_OK) == 0 || ft_strlen(cmd) == 0)
		return (cmd);
	paths = ft_split(get_variable_cmd("PATH"), ":");
	while (paths[++i])
	{
		final = ft_strjoin(ft_strdup(paths[i]), "/");
		final = ft_strjoin(final, cmd);
		if (access(final, X_OK) == 0)
		{
			ft_tab_free(paths);
			free(cmd);
			return (final);
		}
		free(final);
	}
	ft_error(cmd, 127);
	ft_error(": command not found\n", 127);
	free(cmd);
	ft_tab_free(paths);
	return (0);
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
	i = 0;
	current = *lexer_head;
	while (current)
	{
		if (!(current->cmd_struct.cmd[0]))
			current->cmd_struct.cmd[0] = ft_strdup("");
		current->cmd_struct.cmd[0] = get_cmd_path(current->cmd_struct.cmd[0]);
		if (!(current->cmd_struct.cmd[0]))
			while (current->cmd_struct.cmd[++i])
				free(current->cmd_struct.cmd[i]);
		current = current->next;
	}
	
	// TODO! fix variable start with numbers


	
// ------------------------------------------------------------------------









	// print
	
	// current = *lexer_head;
	// t_files *files;

	// while (current)
	// {
	// 	i = 0;
	// 	while (current->cmd_struct.cmd[i])
	// 	{
	// 		printf("%d|%s|\n", i + 1, current->cmd_struct.cmd[i]);
	// 		i++;
	// 	}
	// 	files = current->cmd_struct.files_head;
	// 	while (files)
	// 	{
	// 		printf("file : %s \ttype : %c\n", files->file, files->type);
	// 		files = files->next;
	// 	}
	// 	current = current->next;
	// }



	
	return (1);
}
