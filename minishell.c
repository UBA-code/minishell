/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:44:17 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/25 01:51:22 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_print_lst(t_lexer_node *head)
// {
// 	int	i;

// 	while (head)
// 	{
// 		i = -1;
// 		printf("size of tokens : %zu\n", head->lexer_size);
// 		while (++i < head->lexer_size)
// 		{
// 			printf("content of token : %s\n", head->lexer[i].content);
// 			printf("type of token : %c\n", head->lexer[i].type);
// 		}
// 		head = head->next;
// 	}
// }

// void	ft_putstr(char *str, int fd)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 		write(fd, &str[i], 1);
// }

// void arr(char **arr)
// {
// 	while (arr && *arr)
// 		fprintf(stderr, "CMD : |%s|\n", *arr++);
// }

// void	printtt(t_lexer_node	*head)
// {
// 	t_files	*ff;


// 	while (head)
// 	{
// 		if (head->cmd_struct.cmd)
// 		{
// 			arr(head->cmd_struct.cmd);
// 			puts("");
// 		}
// 		while (head->cmd_struct.files_head)
// 		{
// 			fprintf(stderr, "===> TYPE |%c|", head->cmd_struct.files_head->type);
// 			fprintf(stderr, "===> FILES |%s|",  head->cmd_struct.files_head->file);
// 			head->cmd_struct.files_head = head->cmd_struct.files_head->next;
// 		}
// 		puts("PIPE");
// 		head = head->next;
// 	}
// }

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
		// printtt(head);
		free_parser(head);
		lst_clear(&head);
	}
}


void sig_handler(void)
{
	// if (here_doc_is_closed == 1)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}


int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	char	*line;
	g_global.env_head = 0;
	g_global.error = 0;
	create_env(env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, (void *)sig_handler);
		line = readline("\e[1;32m1337@UBA-shell~> \e[0m"); 
		if (!line)
			break;
		add_history(line);
		if (ft_strlen(line) && check_quotes(line))
			minishell(line, env);
		free(line);
	}
	return 0;
}