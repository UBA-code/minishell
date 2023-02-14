/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:37:08 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/14 11:01:45 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_last_of_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_'))
			return (i);
		i++;
	}
	return (i);
}

// get the variable and join only and spicial characters at end
char	*smart_get_variable(char *str)
{
	char	*variable;
	char	*temp;
	char	*final;
	int		i;

	i = 0;
	final = 0;
	while (str[i])
	{
		temp = get_substring(str, get_last_of_var(str));
		variable = get_variable_cmd(temp);
		if (!variable)
			return (0);
		variable = ft_strjoin(variable, str + get_last_of_var(str));
		free(temp);
		i++;
	}
	return (variable);
}

char	*single_expand(t_lexer_node *node, int *nb)
{
	char	*final;

	final = 0;
	while (++*nb < node->lexer_size && node->lexer[*nb].type != '\'')
		final = ft_strjoin(final, node->lexer[*nb].content);
	return (final);
}

char	*join_string(t_lexer_node *node, int *nb)
{
	char	*final;
	char	*temp;

	final = 0;
	if (node->lexer[*nb].type == '\'')
	{
		final = single_expand(node, nb);
		return (final);
	}
	while (++*nb < node->lexer_size && node->lexer[*nb].type != '"')
	{
		if (node->lexer[*nb].type == '$')
		{
			temp = smart_get_variable(node->lexer[*nb].content + 1);
			if (temp)
			{
				final = ft_strjoin(final, temp);
				free(temp);
			}
		}
		else
			final = ft_strjoin(final, node->lexer[*nb].content);
	}
	return (final);
}
