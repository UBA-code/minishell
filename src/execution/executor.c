/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:59:14 by bahbibe           #+#    #+#             */
/*   Updated: 2023/03/02 18:25:03 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_herdoc(char *limit)
{
	int fd[2];
	char *line;
	int		pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sig_heredoc);
		while (1)
		{
			line = readline("> ");
			if (ft_strlen(line) && ft_strcmp(line, limit))
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			ft_putstr(line, fd[1]);
			ft_putstr("\n", fd[1]);
			free(line);
		}
	}
	else
		wait(&status);
	g_global.error =  exit_stat(status);
	return (close(fd[1]), fd[0]);
}

int	*open_files(t_lexer_node *head)
{
	int *fd;
	
	fd = malloc(sizeof(int) * 2);
	fd[0] = -1;
	fd[1] = -1;
	while (head->cmd_struct.files_head)
	{
		if (head->cmd_struct.files_head->type == 'H')
			fd[0] = head->cmd_struct.files_head->fd; // leaks maybe
			// fd[0] = open_herdoc(head->cmd_struct.files_head->file);
		else if (head->cmd_struct.files_head->type == 'A')
			fd[1] = open(head->cmd_struct.files_head->file, O_CREAT | O_RDWR | O_APPEND, 0777);
		else if (head->cmd_struct.files_head->type == 'O')
			fd[1] = open(head->cmd_struct.files_head->file, O_CREAT | O_RDWR | O_TRUNC, 0777);
		else if (head->cmd_struct.files_head->type == 'I')
		{
			fd[0] = open(head->cmd_struct.files_head->file, O_RDONLY);
			if (fd[0] == -1)
			{
				ft_error(head->cmd_struct.files_head->file, 1);
				ft_error(": no such file or directory\n", 1);
				return (NULL);
			}
		}
		head->cmd_struct.files_head = head->cmd_struct.files_head->next;
	}
	return (fd);
}

void get_file_fd(int *files, int *fd_io)
{
	if (files[0] != -1)
		fd_io[0] = files[0];
	if (files[1] != -1)
		fd_io[1] = files[1];
}

int dup_files(t_lexer_node *head, int pip[2], int tmp, int flag)
{
	int fd_io[2];
	int	*files;
	
	files = open_files(head);
	if (!files)
		return (0);
	fd_io[1] = pip[1];
	fd_io[0] = 0;
	if (flag == FIRST)
		get_file_fd(files, fd_io);
	else if (flag == INPIPE)
	{
		fd_io[0] = tmp;
		get_file_fd(files, fd_io);
	}
	else if (flag == LAST || flag == SINGLE)
	{
		fd_io[1] = 1;
		if (flag == LAST)
			fd_io[0] = tmp;
		get_file_fd(files, fd_io);
	}
	return (dup2(fd_io[0], 0), dup2(fd_io[1], 1));
}

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
		close(*pip);
		dup_files(head, pip, tmp, flag);
		if (!*head->cmd_struct.cmd)
			exit (0);
		execve(*head->cmd_struct.cmd, head->cmd_struct.cmd, head->env);
		ft_error(*head->cmd_struct.cmd, 127);
		ft_error(": command not found\n", 127);
		exit(127);
	}
}

void	executor_builtin(t_lexer_node *head, int pip[2], int tmp, int flag)
{
	dup_files(head, pip, tmp, flag);
	exec_builtin(*head->cmd_struct.cmd, head->cmd_struct.cmd);
	reset_io(g_global.save);
}

void pipeline(t_lexer_node *head)
{
	t_lexer_node	*cur;
	int	 			pip[2];
	int 			tmp;
	// int status;

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
		executor_builtin(head, pip, 0, SINGLE); // ! check the flags and the argument of the function
	else
	{	
		if (head->next == NULL)
			cmd_exec(head, pip, 0, SINGLE);
		else
			pipeline(head);
		while (waitpid(-1, &status, 0) != -1);
		g_global.error = exit_stat(status);
	}
	// g_global.error = 0;
	return (0);
}

int exit_stat(int stat)
{
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat))
		return (WTERMSIG(stat) +128);
	return (0);
}


























































































































// void	cmd_exec(t_lexer_node *head, int pip[2], int tmp, int flag)
// {
// 	pid_t	pid;
// 	int fd[2];

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup_files(head, pip, tmp, flag);
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
