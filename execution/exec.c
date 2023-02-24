/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:59:14 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/19 14:14:41 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exec_fun(t_lexer_node *head)
{
	char **env = head->env;
	char **cmd = head->cmd_struct.cmd;

	execve(cmd[0], cmd, env);
}