/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:59:14 by bahbibe           #+#    #+#             */
/*   Updated: 2023/03/03 00:56:08 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_exec(t_lexer_node *head, int pip[2], int tmp, int flag)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (is_builtin(*head->cmd_struct.cmd))
		{
			dup_files(head, pip, tmp, flag);
			exec_builtin(*head->cmd_struct.cmd, head->cmd_struct.cmd);
			reset_io(g_global.save);
			exit(g_global.error);
		}
		close(pip[0]);
		dup_files(head, pip, tmp, flag);
		if (!*head->cmd_struct.cmd)
			exit (0);
		execve(*head->cmd_struct.cmd, head->cmd_struct.cmd, head->env);
		ft_error(*head->cmd_struct.cmd, 127);
		ft_error(": command not found\n", 127);
		exit(127);
	}
}

void	pipeline(t_lexer_node *head)
{
	t_lexer_node	*cur;
	int				pip[2];
	int				tmp;

	tmp = 0;
	cur = head;
	while (cur)
	{
		pipe(pip);
		if (cur == head)
			cmd_exec(cur, pip, tmp, FIRST);
		else if (cur->next == NULL)
			cmd_exec(cur, pip, tmp, LAST);
		else
			cmd_exec(cur, pip, tmp, INPIPE);
		close(tmp);
		tmp = dup(pip[0]);
		close(pip[0]);
		close(pip[1]);
		cur = cur->next;
	}
}

int	executor(t_lexer_node *head)
{
	int	pip[2];
	int	status;

	if (head->next == NULL && is_builtin(*head->cmd_struct.cmd))
	{
		dup_files(head, pip, 0, SINGLE);
		exec_builtin(*head->cmd_struct.cmd, head->cmd_struct.cmd);
		reset_io(g_global.save);
	}
		// executor_builtin(head, pip, 0, SINGLE);
	else
	{	
		if (head->next == NULL)
			cmd_exec(head, pip, 0, SINGLE);
		else
			pipeline(head);
		while (waitpid(-1, &status, 0) != -1)
			;
		g_global.error = exit_stat(status);
	}
	return (0);
}
