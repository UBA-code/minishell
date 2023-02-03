/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:15:37 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/02 22:06:25 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_next_word(char *str, int i)
{
	while (str[i])
	{
		if (CURRENT_CONDITION)
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
		if (!(CURRENT_CONDITION) && NEXT_CONDITIN)
			len++;
		else if (CURRENT_CONDITION)
			len++;
		i++;
	}
	i--;
	if (CURRENT_CONDITION)
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
		if (!(CURRENT_CONDITION) && NEXT_CONDITIN)
		{
			++(*num);
			return (++i);
		}
		else if (CURRENT_CONDITION)
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
	if (ft_strcmp(content, DOLAR))
		return ('$');
	if (ft_strcmp(content, SPACE))
		return ('S');
	return ('w');
}

void	init_lexer_node(t_cmd_node **head, char *line, char **env)
{
	int			i;
	t_lexer		*lexer;
	int			j;
	t_cmd_node	*node;

	// printf("%d\n", get_token_len(line));
	lexer = malloc(sizeof(t_lexer) * get_token_len(line));
	i = 0;
	j = 0;
	while (line[i])
	{
		lexer[j].content = get_substring(line + i, get_token_size(line + i, &i));
		lexer[j].type = get_type(lexer[j].content);
		j++;
	}
	node = create_node(head);
	node->lexer = lexer;
	node->lexer_size = get_token_len(line);
	node->env = env;                                                                                                                              
}
