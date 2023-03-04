/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:42:16 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/04 18:12:21 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_error(char *cmd)
{
	int	temp;

	if (ft_strchr(cmd, '/') == -1)
	{
		ft_error(cmd, 127);
		ft_error(": command not found\n", 127);
		exit(127);
	}
	if (access(cmd, X_OK))
	{
		ft_error(cmd, 126);
		perror(" ");
		exit(126);
	}
	temp = open(cmd, O_DIRECTORY);
	if (temp != -1)
	{
		close(temp);
		ft_error(cmd, 126);
		ft_error(": is a directory\n", 126);
		exit(126);
	}
}
