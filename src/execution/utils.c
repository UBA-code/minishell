/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:04:41 by bahbibe           #+#    #+#             */
/*   Updated: 2023/03/03 00:57:25 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_file_fd(int *files, int *fd_io)
{
	if (files[0] != -1)
		fd_io[0] = files[0];
	if (files[1] != -1)
		fd_io[1] = files[1];
}

// void	executor_builtin(t_lexer_node *head, int pip[2], int tmp, int flag)
// {
// 	dup_files(head, pip, tmp, flag);
// 	exec_builtin(*head->cmd_struct.cmd, head->cmd_struct.cmd);
// 	reset_io(g_global.save);
// }

void	reset_io(int *save)
{
	dup2(save[0], 0);
	dup2(save[1], 1);
}

int	*save_(void)
{
	int	*save;

	save = malloc(sizeof(int) * 2);
	save[0] = dup(0);
	save[1] = dup(1);
	return (save);
}
