/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:23:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/04 21:52:14 by ybel-hac         ###   ########.fr       */
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

void ft_putstr(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
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
	parser_utils(&head);
	free(args);
	lst_clear(&head);
}

char *get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", 3))
			return (get_substring(env[i] + 4, ft_strlen(env[i] + 4)));
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	char	*line;
	char	*path;
	char	*final_path;

	while (1)
	{
		// line = readline("\e[1;32m1337@UBA-shell~> \e[0m");
		path = get_path(env);
		printf("\e[1;32m");
		final_path = ft_strjoin(path, "/$\e[0m ");
		line = readline(final_path);
		if (ft_strlen(line) && check_quotes(line))
			minishell(line, env);
	}
	// while (1);
	return 0;
}
