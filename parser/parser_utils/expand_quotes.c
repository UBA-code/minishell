/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:37:08 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/15 18:26:12 by ybel-hac         ###   ########.fr       */
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

int	get_dolar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		++i;
	}
	return (i);
}

char	*strjoin_small(char *s1, char c)
{
	char	*final_str;
	int		total_len;
	int		i;

	i = 0;
	total_len = get_str_len(s1) + 1;
	final_str = malloc(sizeof(char) * (total_len + 2));
	if (!final_str)
		return (0);
	if (!s1)
		s1 = get_substring("", 0);
	ft_strcpy(final_str, s1);
	i = get_str_len(final_str);
	final_str[i] = c;
	final_str[i + 1] = 0;
	free(s1);
	return (final_str);
}

// get the variable and join only and spicial characters at end
char	*smart_get_variable(char *str)
{
	char	*variable;
	char	*temp;
	char	*final;
	int		i;

	i = -1;
	final = 0;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			temp = get_substring(str + (i + 1), get_last_of_var(str + (i + 1)));
			variable = get_variable_cmd(temp);
			i = i + get_last_of_var(str + (i + 1));
			free(temp);
			if (!variable)
				continue;
			final = ft_strjoin(final, variable);
		}
		else
			final = strjoin_small(final, str[i]);
	}
	return (final);
}

char	*single_expand(t_lexer_node *node, int *nb)
{
	char	*final;

	final = 0;
	while (++*nb < node->lexer_size && node->lexer[*nb].type != '\'')
		final = ft_strjoin(final, node->lexer[*nb].content);
	return (final);
}

char	*double_expand(t_lexer_node *node, int *nb)
{
	char	*final;
	char	*temp;

	final = 0;
	while (++*nb < node->lexer_size && node->lexer[*nb].type != '"')
	{
		temp = smart_get_variable(node->lexer[*nb].content);
		final = ft_strjoin(final, temp);
		free(temp);
	}
	return (final);
}

char	*join_string(t_lexer_node *node, int *nb)
{
	char	*final;
	char	*temp;

	final = 0;
	while (*nb < node->lexer_size && node->lexer[*nb].type != 'S')
	{
		if (node->lexer[*nb].type == '\'')
			temp = single_expand(node, nb);
		else if (node->lexer[*nb].type == '"')
			temp = double_expand(node, nb);
		else
			temp = smart_get_variable(node->lexer[*nb].content);
		if (temp)
		{
			final = ft_strjoin(final, temp);
			free(temp);
		}
		++*nb;
	}
	return (final);
}

int	check_export_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| (str[i] == '_') || str[i] == '='))
			return (0);
		i++;
	}
	return (1);
}
