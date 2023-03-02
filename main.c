/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:44:17 by bahbibe           #+#    #+#             */
/*   Updated: 2023/03/02 13:46:46 by bahbibe          ###   ########.fr       */
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
		return ft_error("syntax error\n", 258);
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

char *get_folder(char *s1, char *s2, char *s3)
{
	char *final;

	final = ft_strjoin(0, s1);
	final = ft_strjoin(final, s2);
	final = ft_strjoin(final, s3);
	free(s2);
	return (final);
}

// void sig_heredoc(int sig)
// {
// 	if (sig == SIGINT)
// 		exit(EXIT_FAILURE);
// }

// void sig_handl(int sig)
// {
// 	if (sig == SIGINT && !g_global.open_heredoc)
// 	{
// 		printf("\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

int *save_(void)
{
	int *save = malloc(sizeof(int) * 2);
	save[0] = dup(0);
	save[1] = dup(1);
	return (save);
}

void reset_io(int *save)
{
	dup2(save[0], 0);
	dup2(save[1], 1);
}


int main(int ac, char **av, char **env)
{
	(void)    ac;
	(void)    av;
	char    *line;

	g_global.save = save_();
	g_global.env_head = 0;
	g_global.error = 0;
	create_env(env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		line = readline("\e[1;32mMinishell~> \e[0m");
		signal(SIGINT, SIG_IGN);
		if (!line)
			break;
		if (ft_strlen(line))
		{
			add_history(line);
			minishell(line, env);
			reset_io(g_global.save);
		}
		
		free(line);
	}
	return 0;
}



// int main(int argc, char const *argv[])
// {
// 	char **temp;
// 	int		i;

// 	i = -1;
// 	temp = ft_split_costom("\"\"");
// 	while (temp[++i])
// 		printf("*%s*\n", temp[i]);
// 	return 0;
// }
