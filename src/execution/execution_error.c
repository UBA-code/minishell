/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:42:16 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/04 18:48:06 by ybel-hac         ###   ########.fr       */
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


int	open_file(char *file, char flag)
{
	int	fd;

	if (flag == 'A')
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (flag == 'O')
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	return (fd);
}