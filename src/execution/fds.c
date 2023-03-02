/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:07:46 by bahbibe           #+#    #+#             */
/*   Updated: 2023/03/02 23:44:50 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int open_input(t_files *file)
{
	int fd;
	
	fd = open(file->file, O_RDONLY);
	if (fd == -1)
	{
		perror(file->file);
		exit(EXIT_FAILURE);
	}
	return(fd);
}

int	*redirect(t_lexer_node *head)
{
	int *fd;
	
	fd = malloc(sizeof(int) * 2);
	fd[0] = -1;
	fd[1] = -1;
	while (head->cmd_struct.files_head)
	{
		if (head->cmd_struct.files_head->type == 'H')
			fd[0] = head->cmd_struct.files_head->fd;
		else if (head->cmd_struct.files_head->type == 'A')
			fd[1] = open(head->cmd_struct.files_head->file,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (head->cmd_struct.files_head->type == 'O')
			fd[1] = open(head->cmd_struct.files_head->file,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (head->cmd_struct.files_head->type == 'I')
			fd[0] = open_input(head->cmd_struct.files_head);
		head->cmd_struct.files_head = head->cmd_struct.files_head->next;
	}
	return (fd);
}

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
	if (g_global.error)
	{
		printf("\n");
		g_global.done = 1;
	}
	return (close(fd[1]), fd[0]);
}

int dup_files(t_lexer_node *head, int pip[2], int tmp, int flag)
{
	int fd_io[2];
	int	*files;
	
	files = redirect(head);
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

