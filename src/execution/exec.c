/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:59:14 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/22 20:33:21 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	herdoc(char *limit)
{
	int fds[2];
	char *line;

	pipe(fds);
	while (1)
	{
		line = readline("> ");
		if (ft_memcmp(line, limit, ft_strlen(line) + 1) == 0)
		{
			free(line);
			break;
		}
		ft_putstr(line, fds[1]);
		ft_putstr("\n", fds[1]);
		free(line);
	}
	close(fds[1]);
	return (*fds);
}








void	run_cmdexc(t_executor *head)
{
	pid_t	pid;
	int		fd_write;
	int		fd_read;

	struct s_stat statss;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_write, 1);
		dup2(fd_read, 0);
		if (!**head->cmd_struct.cmd)
			exit(127);
		stat(*head->cmd_struct.cmd,statss );
		if (IS_DERCETORY(stat.s_mode))
		{
			strerror(EISDIR);
			exit(126);
		}
		execve(*head->cmd_struct.cmd, head->cmd_struct.cmd, head->env);
		if (errno == EACCES)
		{
			strerror(EACCES);
			exit(126);
		}
	}
	int status;
	wait(&status);
	g_global.error = WEXITSTATUS(status);
}


int	*open_file(t_files *head)
{
	int *fd_io = malloc(sizeof(int) * 2);
	
	*fd_io = -2;
	*(fd_io + 1) = -2;
	// while (head->cmd_struct.files_head)
	// {
	// 	close(fd_read);
	// 	close(fd_write);
	// 	if (tyepe == herdoc)
	// 		*fd_io = herdoc();
	// 	if (type == APPEND)
	// 		fd_write = open(head->cmd_struct.files_head->file, O_CREAT | O_RDWR | O_APPEND);
	// 	if (type == OUTPUT)
	// 		fd_write = open(head->cmd_struct.files_head->file, O_CREAT | O_RDWR | O_TRUNC);
	// 	if (type == INPUT)
	// 		fd_read = open(head->cmd_struct.files_head->file, O_RDONLY);
	// 	head->cmd_struct.files_head->file;
	// }
	return (fd_io);
}


void run_pipeline(t_executor *head)
{
	int		*fd_io;
	int		fds[2];
	pid_t	pid;
	int		fd_tmp;

	
	while (head)
	{

		pipe(fds);
		if (index == 1)
		{
			pid = fork();
			if (pid == 0)
			{
								fd_io = open_file(head->cmd_struct.files_head);
								dup2(fd_io[0], 0);
								
								
								if (fd_io[1] != -2)
									dup2(fds[1], 1);
								else
									dup2(fd_io[1], 1);

									
			// 				if (!**head->cmd_struct.cmd)
			// 				exit(127);
			// 			stat(*head->cmd_struct.cmd,statss );
			// 			if (IS_DERCETORY(stat.s_mode))
			// 			{
			// 				strerror(EISDIR);
			// 				exit(126);
			// 			}
			// 			execve(*head->cmd_struct.cmd, head->cmd_struct.cmd, head->env);
			// 			if (errno == EACCES)
			// 			{
			// 				strerror(EACCES);
			// 				exit(126);
			// 			}
			// }
		}
		
		
		else if (head->next == NULL)
		{
				fd_io = open_file(head->cmd_struct.files_head);
					if (fd_io[0] != -2)
						dup2(fd_tmp, 0);
					else
						dup2(fd_io[0], 0);
	
					if (fd_io[1] != -2)
						dup2(fd_io[1], 1);

				// execcution;
		}
		
	
		else	
		{
					fd_io = open_file(head->cmd_struct.files_head);
					
					if (fd_io[0] == -2)
						dup2(fd_tmp, 0);
					else
						dup2(fd_io[0], 0);
					

					if (fd_io[1] == -2)
						dup2(fds[1], 1);
					else
						dup2(fd_io[1], 1);
				// exucetion
		}
		
		close(fd_tmp);
		fd_tmp = dup(fds[0]);
		close(*fds);
		close(fds[1]);
		head = head->next;
	}	

	int status;

	while (wait(&status) != -1)
		;
	g_global.error = WEXITSTATUS(status); 
}


int  executor(t_executor *head)
{
	if (!head)
		return (0);
	if (head->next == NULL)
		run_cmdexc(head);
	else
		run_pipeline(head);
	return (EXIT_SUCCESS);
}
