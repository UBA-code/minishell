/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:34:10 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/28 18:54:22 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_element_size(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i] == '|');
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[i + 1] && str[++i] != '\'');
		else if (str[i] == '"')
			while (str[i + 1] && str[++i] != '\"');
		if (str[i] != '|' && (str[i + 1] == '|' || str[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

char **ft_split_costom(char *str)
{
	char	**final;
	int		i;
	int		j;
	int		x;

	i = -1;
	x = 0;
	final = malloc(sizeof(char *) * (get_element_size(str) + 1));
	while (str[++i] == '|');
	j = i;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[i + 1] && str[++i] != '\'');
		else if (str[i] == '"')
			while (str[i + 1] && str[++i] != '\"');
		if (str[i] != '|' && (str[i + 1] == '|' || str[i + 1] == '\0'))
		{
			final[x++] = ft_substr(str, j, i - j + 1);
			j = i + 2;
		}
		i++;
	}
	final[x] = 0;
	return (final);
}
