/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:59:14 by bahbibe           #+#    #+#             */
/*   Updated: 2023/03/05 11:38:11 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_herdoc(char *limit, int flag)
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
			if (!line)
				exit(EXIT_SUCCESS);
			if (ft_strlen(line) && ft_strcmp(line, limit))
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			if (!flag)
				ft_putstr(line, fd[1]);
			else
				ft_putstr(smart_get_variable(line, 1), fd[1]);
			ft_putstr("\n", fd[1]);
			free(line);
		}
	}
	else
		wait(&status);
	g_global.error =  exit_stat(status);
	if (g_global.error)
	{
		printf("\n");
		g_global.done = 1;
	}
	return (close(fd[1]), fd[0]);
}

int	*open_files(t_lexer_node *head)
{
	int		*fd;
	t_files	*current;

	current = head->cmd_struct.files_head;
	fd = malloc(sizeof(int) * 2);
	fd[0] = -1;
	fd[1] = -1;
	while (current)
	{
		if (current->type == 'H')
			fd[0] = current->fd;
		else if (current->type == 'A')
			fd[1] = open_file(current->file, 'A');
		else if (current->type == 'O')
			fd[1] = open_file(current->file, 'O');
		else if (current->type == 'I')
			fd[1] = open_file(current->file, 'I');
		current = current->next;
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

int *dup_files(t_lexer_node *head, int pip[2], int tmp, int flag)
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
	dup2(fd_io[1], 1);
	return (dup2(fd_io[0], 0), files);
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
		check_error(*head->cmd_struct.cmd);
		execve(*head->cmd_struct.cmd, head->cmd_struct.cmd, head->env);
		perror("");
		exit(127);
	}
}

void	executor_builtin(t_lexer_node *head, int pip[2], int tmp, int flag)
{
	int	*files;

	files = dup_files(head, pip, tmp, flag);
	exec_builtin(*head->cmd_struct.cmd, head->cmd_struct.cmd);
	reset_io(g_global.save);
	free(files);
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
		executor_builtin(head, pip, 0, SINGLE);
	else
	{	
		if (head->next == NULL)
			cmd_exec(head, pip, 0, SINGLE);
		else
			pipeline(head);
		while (waitpid(-1, &status, 0) != -1);
		g_global.error = exit_stat(status);
	}
	return (0);
}

int exit_stat(int stat)
{
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat))
		return (WTERMSIG(stat) + 128);
	return (0);
}
