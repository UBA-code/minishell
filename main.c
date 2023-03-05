/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:44:17 by bahbibe           #+#    #+#             */
/*   Updated: 2023/03/06 00:48:16 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	minishell(char *line, char **env)
{
	char			**args;
	int				i;
	t_lexer_node	*head;

	if (!check_syntax(line))
		return (ft_error("minishell: syntax error\n", 258));
	head = 0;
	i = -1;
	args = ft_split_costom(line);
	while (args[++i])
		if (!check_quotes(args[i]))
			return (tab_free(args));
	i = -1;
	while (args[++i])
	{	
		init_lexer_node(&head, args[i], env);
		// free(args[i]);
	}
	free(args);
	if (parser_utils(&head))
	{
		g_global.head = head;
		executor(head);
		free_parser(head);
		lst_clear(&head);
	}
}

int	main(int ac, char **av, char **env)
{
	char			*line;

	init_var(ac, av, env);
	while (1)
	{
		g_global.open_heredoc = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		line = readline("\e[1;32mMinishell~> \e[0m");
		signal(SIGINT, SIG_IGN);
		if (!line)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (ft_strlen(line) && check_empty(line))
		{
			add_history(line);
			minishell(line, env);
			reset_io(g_global.save);
		}
		free(line);
	}
	return (0);
}
