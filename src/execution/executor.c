/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:59:14 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/26 17:08:02 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
# include <string.h>

int	open_herdoc(char *limit)
{
	int fd[2];
	char *line;

	pipe(fd);
	while (1)
	{
		// line = readline("> ");
		ft_putstr("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		//ft_strchr(line, "$");//
		if (ft_strncmp(line, limit, ft_strlen(line) - 1)) // fodbidden function: memcmp
		{
			free(line);
			break;
		}
		ft_putstr(line, fd[1]);
		ft_putstr("\n", fd[1]);
		free(line);
	}
	return (close(fd[1]), fd[0]);
}

int	*open_files(t_lexer_node *head)
{
	int *fd = malloc(sizeof(int) * 2);
	fd[0] = -1;
	fd[1] = -1;
	// if (!head->cmd_struct.files_hea÷d)
		
	while (head->cmd_struct.files_head)
	{
		if (head->cmd_struct.files_head->type == 'H')
			fd[0] = open_herdoc(head->cmd_struct.files_head->file);
		else if (head->cmd_struct.files_head->type == 'A')
			fd[1] = open(head->cmd_struct.files_head->file, O_CREAT | O_RDWR | O_APPEND, 0777);
		else if (head->cmd_struct.files_head->type == 'O')
			fd[1] = open(head->cmd_struct.files_head->file, O_CREAT | O_RDWR | O_TRUNC, 0777);
		else if (head->cmd_struct.files_head->type == 'I')
			fd[0] = open(head->cmd_struct.files_head->file, O_RDONLY);
		head->cmd_struct.files_head = head->cmd_struct.files_head->next;
	}
	return (fd);
}

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
	if (is_builtin(*head->cmd_struct.cmd))
	{
		dup_files(head, fds, tmp, flag);
		exec_builtin(*head->cmd_struct.cmd, head->cmd_struct.cmd);
		reset_io(g_global.save);
	}
	pid = fork();
	if (pid == 0)
	{
		close(*fds);
		dup_files(head, fds, tmp, flag);
		execve(*head->cmd_struct.cmd, head->cmd_struct.cmd, head->env);
		if (errno == EACCES)
			exit(126);
	}
}

void pipeline(t_lexer_node *head)
{
	t_lexer_node	*crr;
	int	 			fds[2];
	int 			tmp;

	tmp = 0;
	crr = head;
	while (crr)
	{
		pipe(fds);
		if (head == crr)
			cmd_exec(crr, fds, tmp, 1);
		else if (crr->next == NULL)
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
		cmd_exec(head, fds, 0, 4);
	else
		pipeline(head);
	while (waitpid(-1, &status, 0) != -1)
		;
	g_global.error = WEXITSTATUS(status);
	// if (!head)
	// print_lex(head);
	
	return (0);
}



























































































































// void	cmd_exec(t_lexer_node *head, int fds[2], int tmp, int flag)
// {
// 	pid_t	pid;
// 	int fd[2];

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup_files(head, fds, tmp, flag);
// 		if (!**head->cmd_struct.cmd)
// 			exit(127);
// 		if (access(*head->cmd_struct.cmd, X_OK) == -1)
// 			exit(126);
// 		execve(*head->cmd_struct.cmd, head->cmd_struct.cmd, head->env);
// 	}
// }






















// void pipeline(t_lexer_node *head)
// {
// 	t_lexer_node *curr;
// 	int		*fd_io;
// 	int		fd[2];
// 	// pid_t	pid;
// 	int		fd_tmp;
// 	// int		status;

// 	fd_tmp = -1;
// 	curr = head;
// 	while (curr)
// 	{
// 		pipe(fd);
// 		if (curr == head)
// 		{
// 			// pid = fork();
// 			// if (pid == 0)
// 			// {
// 				print_lex(curr);
// 				fd_io = open_files(curr);
// 				dup2(fd_io[0], 0);
// 				if (fd_io[1] != -1)
// 					dup2(fd[1], 1);
// 				else
// 					dup2(fd_io[1], 1);
// 				cmd_exec(curr);
// 			// }
// 		}
// 		else if (curr->next == NULL)
// 		{
// 			fd_io = open_files(curr);
// 				if (fd_io[0] != -1)
// 					dup2(fd_tmp, 0);
// 				else
// 					dup2(fd_io[0], 0);

// 				if (fd_io[1] != -1)
// 					dup2(fd_io[1], 1);
// 				cmd_exec(curr);
// 		}
// 		else	
// 		{
// 			fd_io = open_files(curr);
// 			if (fd_io[0] == -1)
// 				dup2(fd_tmp, 0);
// 			else
// 				dup2(fd_io[0], 0);
// 			if (fd_io[1] == -1)
// 				dup2(fd[1], 1);
// 			else
// 				dup2(fd_io[1], 1);
// 			cmd_exec(curr);
// 		}
// 		curr = curr->next;
// 	}	
// 	close(fd_tmp);
// 	fd_tmp = dup(fd[0]);
// 	close(fd[0]);
// 	close(fd[1]);

	
	
// }

// int	executor(t_lexer_node *head)
// {
// 	int status;
	
// 	if (!head)
// 		return (0);
// 	if (head->next == NULL)
// 	{
// 		if (is_builtin(*head->cmd_struct.cmd))
// 			exec_builtin(*head->cmd_struct.cmd, head->cmd_struct.cmd);
// 		else
// 			cmd_exec(head);
// 	}
// 	else
// 		pipeline(head);
// 	while (waitpid(-1, &status, 0) != -1)
// 		;
// 	g_global.error = WEXITSTATUS(status); 
// 	return (0);
// }
