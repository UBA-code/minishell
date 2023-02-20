/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:59:14 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/19 19:25:09 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize(t_lexer_node *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
int exec_fun(t_lexer_node *head)
{
	char **env = head->env;
	
	
	// int fd[2];
	// pipe(fd);
	// int pid = fork();
	// if (pid == 0)
	// {
	
	// 	execve(cmd[0], cmd, env);
	// }
	// cmd = head->next->cmd_struct.cmd;
	// int pid1 = fork();
	// if (pid1 == 0)
	// {
	// 	close(fd[1]);
	// 	dup2(fd[0], 0);
	// 	execve(cmd[0], cmd, env);
	// }
	// close(fd[1]);
	// close(fd[1]);
	// while (waitpid(0, NULL, 0) != -1);
	// printf("%s %s %s\n", cmd[0], cmd[1], cmd[2]);

	t_lexer_node *tmp = head;
	int in = dup(0);
	int out = dup(1);
	int pid ;
	
	if (ft_lstsize(head) < 2)
	{
		pid = fork();
		if (!pid)
			execve(tmp->cmd_struct.cmd[0], tmp->cmd_struct.cmd, env);
	}
	else 
		while (tmp)
		{
			int fd[2];
			pipe(fd);
			
			if (!pid)
			{
				dup2(fd[0], 0);
				dup2(fd[1], 1);
				execve(tmp->cmd_struct.cmd[0], tmp->cmd_struct.cmd, env);
			}
			close(fd[0]);
			close(fd[1]);
			int stat;
			waitpid(pid, &stat, 0);
			if(stat)
				return (stat);
		}
}