/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:18:07 by bahbibe           #+#    #+#             */
/*   Updated: 2023/03/02 18:28:38 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void sig_handler(int sig)
{
	if (sig == SIGINT)
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void sig_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_FAILURE);
}

// void sig_handler_cmd(int sig)
// {
// 	//(void)sig;
// 	if (sig == SIGINT)
// 		exit_stat(130);
// }
