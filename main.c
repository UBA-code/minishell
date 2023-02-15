/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:23:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/15 11:59:55 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void ft_print_lst(t_lexer_node *head)
{
	int i;

	while (head)
	{
		i = -1;
		printf("size of tokens : %zu\n", head->lexer_size);
		while (++i < head->lexer_size)
		{
			printf("content of token : %s\n", head->lexer[i].content);
			printf("type of token : %c\n", head->lexer[i].type);
		}
		head = head->next;
	}
}

void ft_putstr(char *str, int fd)
{
	int i;

	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
}

void minishell(char *line, char **env)
{
	char **args;
	int i;
	t_lexer_node *head;

	head = 0;
	i = 0;
	args = ft_split(line, "|");
	while (args[i])
	{
		init_lexer_node(&head, args[i], env);
		free(args[i]);
		i++;
	}
	// i = 0;
	// while (i < head->lexer_size)
	// {
	// 	printf("%s %c\n", head->lexer[i].content, head->lexer[i].type);
	// 	i++;
	// }
	free(args);
	parser_utils(&head);
	free_parser(head);
	system("leaks minishell");
	lst_clear(&head);
}

int main(int ac, char **av, char **env)
{
	char	*line;

	g_global.env_head = 0;
	create_env(&(g_global.env_head), env);
	// printf("--------------------------------------------\n");
	// export_cmd(&(g_global.env_head), "name=\"\"");
	// export_cmd(&(g_global.env_head), 0);
	// env_cmd(g_global.env_head);
	while (1)
	{
		line = readline("\e[1;32m1337@UBA-shell~> \e[0m");
		add_history(line);
		if (ft_strlen(line) && check_quotes(line))
			minishell(line, env);
		free(line);
		// system("leaks minishell");
	}
	// while (1);
	return 0;
}
