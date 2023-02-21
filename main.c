/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:23:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/21 15:05:10 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_print_lst(t_lexer_node *head)
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

void	ft_putstr(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
}

void	minishell(char *line, char **env)
{
	char			**args;
	int				i;
	t_lexer_node	*head;

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
	if (parser_utils(&head))
	{
	// exec_fun(head);
		env_cmd('x');
		free_parser(head);
		lst_clear(&head);
	}
}

void	str_start(void)
{
	ft_putstr("\n\e[1;32m\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
																	\n\
", 1);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	g_global.env_head = 0;
	g_global.error = 0;
	create_env(env);
	while (1)
	{
		line = readline("\e[1;32m1337@UBA-shell~> \e[0m");
		add_history(line);
		if (ft_strlen(line) && check_quotes(line))
			minishell(line, env);
		free(line);
	}
	return (0);
}
