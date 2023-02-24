/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:23:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/24 16:49:24 by ybel-hac         ###   ########.fr       */
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
		cd_cmd(head->cmd_struct.cmd);
		free_parser(head);
		lst_clear(&head);
	}
}

char *get_folder(char *s1, char *s2, char *s3)
{
    char *final;

    final = ft_strjoin(0, s1);
    final = ft_strjoin(final, s2);
    final = ft_strjoin(final, s3);
    free(s2);
    return (final);
}

int main(int ac, char **av, char **env)
{
    (void)    ac;
    (void)    av;
    char    *line;
    char    *temp;

    g_global.env_head = 0;
    g_global.error = 0;
    create_env(env);
    while (1)
    {
        temp = get_folder("\e[1;32m", getcwd(0, 0), "~> \e[0m");
        line = readline(temp);
        free(temp);
        if (!line)
            break;
        add_history(line);
        if (ft_strlen(line) && check_quotes(line))
            minishell(line, env);
        
        free(line);
    }
    return 0;
}
