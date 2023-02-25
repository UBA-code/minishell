/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:59:14 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/25 11:33:26 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	herdoc(char *limit)
{
	int fd[2];
	char *line;

	pipe(fd);
	while (1)
	{
		line = readline("> "); // i think here need gnl not readline because of tab's
		if (ft_strncmp(line, limit, ft_strlen(line) + 1) == 0)
		{
			free(line);
			break;
		}
		ft_putstr(line, fd[1]);
		ft_putstr("\n", fd[1]);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

void	cmd_exec(t_lexer_node *head)
{
	pid_t	pid;
	int fd[2];
	int status;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		dup2(fd[0], 0);
		if (!**head->cmd_struct.cmd)
			exit(127);
		if (access(*head->cmd_struct.cmd, X_OK) == -1)
			exit(126);
		execve(*head->cmd_struct.cmd, head->cmd_struct.cmd, head->env);
	}
}


int	*open_files(t_lexer_node *head)
{
	int *fd = malloc(sizeof(int) * 2);
	fd[0] = -1;
	fd[1] = -1;
	while (head->cmd_struct.files_head->next)
	{
		close(fd[0]);
		close(fd[1]);
		if (head->cmd_struct.files_head->type == 'H')
			fd[0] = herdoc(head->cmd_struct.cmd[0]);
		else if (head->cmd_struct.files_head->type == 'A')
			fd[1] = open(head->cmd_struct.files_head->file, O_CREAT | O_RDWR | O_APPEND);
		else if (head->cmd_struct.files_head->type == 'O')
			fd[1] = open(head->cmd_struct.files_head->file, O_CREAT | O_RDWR | O_TRUNC);
		else if (head->cmd_struct.files_head->type == 'I')
			fd[0] = open(head->cmd_struct.files_head->file, O_RDONLY);
		head->cmd_struct.files_head = head->cmd_struct.files_head->next;
	}
	return (fd);
}

void pipeline(t_lexer_node *head)
{
	int		*fd_io;
	int		fd[2];
	pid_t	pid;
	int		fd_tmp;
	int		status;

	while (head)
	{
		pipe(fd);
		if (index == 1)
		{
			pid = fork();
			if (pid == 0)
			{
				fd_io = open_files(head->cmd_struct.files_head);
				dup2(fd_io[0], 0);
				if (fd_io[1] != -1)
					dup2(fd[1], 1);
				else
					dup2(fd_io[1], 1);
				cmd_exec(head);
			}
		}
		else if (head->next == NULL)
		{
			fd_io = open_files(head->cmd_struct.files_head);
				if (fd_io[0] != -1)
					dup2(fd_tmp, 0);
				else
					dup2(fd_io[0], 0);

				if (fd_io[1] != -1)
					dup2(fd_io[1], 1);
				cmd_exec(head);
		}
		else	
		{
			fd_io = open_files(head->cmd_struct.files_head);
			if (fd_io[0] == -1)
				dup2(fd_tmp, 0);
			else
				dup2(fd_io[0], 0);
			if (fd_io[1] == -1)
				dup2(fd[1], 1);
			else
				dup2(fd_io[1], 1);
			cmd_exec(head);
		}
	}	
	close(fd_tmp);
	fd_tmp = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
	head = head->next;
	while (waitpid(-1, &status, 0) != -1)
		;
	g_global.error = WEXITSTATUS(status); 
}


int	executor(t_lexer_node *head)
{
	if (!head)
		return (0);
	if (head->next == NULL )
	{
		if (is_builtin(*head->cmd_struct.cmd))
			
		cmd_exec(head);
	}
	else
		pipeline(head);
	return (EXIT_SUCCESS);
}
