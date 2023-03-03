/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:44:17 by bahbibe           #+#    #+#             */
/*   Updated: 2023/03/03 02:17:39 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

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

	if (!check_syntax(line))
		return (ft_error("syntax error\n", 258));
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
		free(args[i]);
	}
	free(args);
	if (parser_utils(&head))
	{
		
		executor(head);
		// exec_builtin(*head->cmd_struct.cmd, head->cmd_struct.cmd);
		free_parser(head);
		lst_clear(&head);
	}
}

char	*get_folder(char *s1, char *s2, char *s3)
{
	char	*final;

	final = ft_strjoin(0, s1);
	final = ft_strjoin(final, s2);
	final = ft_strjoin(final, s3);
	free(s2);
	return (final);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void) ac;
	(void) av;
	g_global.save = save_();
	g_global.env_head = 0;
	g_global.error = 0;
	create_env(env);
	while (1)
	{
		g_global.done = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		line = readline("\e[1;32mMinishell~> \e[0m");
		signal(SIGINT, SIG_IGN);
		if (!line)
			break ;
		if (ft_strlen(line))
		{
			add_history(line);
			minishell(line, env);
			reset_io(g_global.save);
		}
		free(line);
	}
	return (0);
}
