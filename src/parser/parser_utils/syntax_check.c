/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:02:19 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/27 20:51:40 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_pipes_len(char *line)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (line[++i])
		if (line[i] == '|')
			j++;
	return (j);
}

int	check_pipes(char *line)
{
	int		i;
	int		tab_len;
	int		pipes_len;
	char	**temp;

	temp = ft_split(line, "|");
	while (temp[tab_len])
		tab_len++;
	pipes_len = get_pipes_len(line);
	i = 0;
	while (line[i])
	{
		
		i++;
	}
	return (1);
}

int	check_syntax(char *line)
{
	if (!check_pipes(line))
		return (0);
	return (1);
}
