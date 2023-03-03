/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:15:37 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/03 13:51:42 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	lexer_check(char c)
{
	if (c == '\'' || c == '"' || c == '<' || c == '>'
		|| c == ' ' || c == '	')
		return (1);
	return (0);
}

int	get_next_word(char *str, int i)
{
	while (str[i])
	{
		if (lexer_check(str[i]))
			return (i);
		++i;
	}
	return (i);
}

// get how mush tokens
int	get_token_len(char *str)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (!(lexer_check(str[i])) && lexer_check(str[i + 1]))
			len++;
		else if (lexer_check(str[i]))
			len++;
		i++;
	}
	i--;
	if (lexer_check(str[i]))
		return (len);
	return (++len);
}

// get len of token
int	get_token_size(char *str, int *num)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (!(lexer_check(str[i])) && lexer_check(str[i + 1]))
		{
			++(*num);
			return (++i);
		}
		else if (lexer_check(str[i]))
		{
			++(*num);
			return (1);
		}
		++(*num);
		i++;
	}
	return (i);
}

char	get_type(char *content)
{
	if (ft_strcmp(content, LEFT_REDIRECT))
		return ('>');
	if (ft_strcmp(content, RIGHT_REDIRECT))
		return ('<');
	if (ft_strcmp(content, DOUBLE_QUOTES))
		return ('"');
	if (ft_strcmp(content, SINGLE_QUOTES))
		return ('\'');
	if (ft_strcmp(content, LEFT_GROUP))
		return ('(');
	if (ft_strcmp(content, RIGHT_GROUP))
		return (')');
	if (ft_strcmp(content, SPACE))
		return ('S');
	if (ft_strcmp(content, TAB))
		return ('T');
	else
		return ('W');
}
