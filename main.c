/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:23:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/01 13:50:44 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_print_lst(t_cmd_node *head)
{
	int	i;

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

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

void	minishell(char *line, char **env)
{
	char	**args;
	int		i;
	t_cmd_node	*head;

	head = 0;
	i = 0;
	args = ft_split(line, "|");
	while (args[i])
	{
		init_lexer_node(&head, args[i], env);
		free(args[i]);
		i++;
	}
	free(args);
	ft_print_lst(head);
	lst_clear(&head);
}

int	main(int ac, char **av, char **env)
{
	char		*line;

	while (1)
	{
		line = readline("\e[32m1337@UBA-shell~> ");
		if (ft_strlen(line))
			minishell(line, env);
	}
	// while (1);
	return 0;
}
