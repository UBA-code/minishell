/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:59:09 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/25 11:19:59 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// double quotes check
int	check_dbquotes(char *str, int *i, int j)
{
	j = *i + 1;
	while (str[j])
	{
		if (str[j] == '\'')
		{
			*i = j;
			break ;
		}
		j++;
	}
	if (*i != j)
	{
		ft_error("Error, Unclosed Quotes\n", 258);
		return (0);
	}
	return (1);
}

// single quotes check
int	check_squotes(char *str, int *i, int j)
{
	j = *i + 1;
	while (str[j])
	{
		if (str[j] == '"')
		{
			*i = j;
			break ;
		}
		j++;
	}
	if (*i != j)
	{
		ft_error("Error, Unclosed Quotes\n", 258);
		return (0);
	}
	return (1);
}

int	check_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			if (!check_dbquotes(str, &i, j))
				return (0);
		if (str[i] == '"')
			if (!check_squotes(str, &i, j))
				return (0);
		i++;
	}
	return (1);
}

void	ft_error(char *str, int error)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	g_global.error = error;
}
