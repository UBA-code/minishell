/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:46:14 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/25 11:21:15 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// get the variable and join only and spicial characters at end
char	*smart_get_variable(char *str)
{
	t_get_variable_struct	utils;
	char					*error_num;

	utils.i = -1;
	utils.final = 0;
	utils.string = str;
	while (str[++(utils.i)])
	{
		if (str[utils.i] == '$' && str[utils.i + 1] == '?')
		{
			error_num = ft_itoa(g_global.error);
			utils.final = ft_strjoin(utils.final, error_num);
			free(error_num);
			utils.i += 2;
		}
		if (str[utils.i] == '$' && speciale_check(str[utils.i + 1], &(utils.i)))
		{
			if (dolar_work(&utils))
				continue ;
		}
		else
			utils.final = strjoin_small(utils.final, str[utils.i]);
	}
	return (utils.final);
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
				|| (str[i] == '_')))
			return (0);
		i++;
	}
	return (1);
}
