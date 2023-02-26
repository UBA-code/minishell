/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 09:49:32 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/26 10:31:04 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int dup_files(t_lexer_node *head, int fds[2], int tmp, int flag)
{
	int fd_src;
	int fd_dest;
	int	*files;
	
	files = open_files(head);
	fd_dest = fds[1];
	fd_src = 0;
	if (flag == 1)
	{
		if (files[0] != -1)
			fd_src = files[0];
		if (files[1] != -1)
			fd_dest = files[1];
	}
	else if (flag == 2)
	{
		fd_src = tmp;
		if (files[0] != -1)
			fd_src = files[0];
		if (files[1] != -1)
			fd_dest = files[1];
	}
	else if (flag == 3 || flag == 4)
	{
		fd_dest = 1;
		if (flag == 3)
			fd_src = tmp;
		if (files[0] != -1)
			fd_src = files[0];
		if (files[1] != -1)
			fd_dest = files[1];
	}
	return (dup2(fd_src, 0), dup2(fd_dest, 1));
}

void	cmd_exec(t_lexer_node *head, int fds[2], int tmp, int flag)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!**head->cmd_struct.cmd)
			exit(127);
		if (access(*head->cmd_struct.cmd, X_OK) == -1)
			exit(126);
		dup_files(head, fds, tmp, flag);
		execve(*head->cmd_struct.cmd, head->cmd_struct.cmd, head->env);
	}
}


void pipeline(t_lexer_node *head)
{
	t_lexer_node	*crr;
	int	 			fds[2];
	int 			tmp;

	crr = head;
	while (crr)
	{
		pipe(fds);
		if (head == crr)
		{
			fprintf(stderr, "in here\n");
			cmd_exec(crr, fds, tmp, 1);
		}
		else if (head->next == NULL)
			cmd_exec(crr, fds, tmp, 3);
		else
			cmd_exec(crr, fds, tmp, 2);
		crr = crr->next;
		close(tmp);
		tmp = dup(*fds);
		close(fds[0]);
		close(fds[1]);
	}
}



int	executor(t_lexer_node *head)
{
	int status;
	int	fds[2];
	
	if (head->next == NULL)
	{
		if (is_builtin(*head->cmd_struct.cmd))
			exec_builtin(*head->cmd_struct.cmd, head->cmd_struct.cmd);
		else
			cmd_exec(head, fds, 0, 4);
	}
	else
		pipeline(head);
	while (waitpid(-1, &status, 0) != -1)
		;
	g_global.error = WEXITSTATUS(status); 
	return (0);
}
 