/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:37:08 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/12 14:39:48 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_copy_single(char *src)
{
	int		i;
	char	*str;

	i = 0;
	while (src[++i])
		if (src[i] == '\'' && !(src[i + 1]))
			break;
	str = get_substring(src + 1, i);
	free(src);
	return (str);
}

int	get_variable_length(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| (str[i] == '_')))
			return (i);
		i++;
	}
	return (i);
}

char	*loop_check_variable(char *str, int len)
{
	t_mini_env	*current;

	current = g_global.env_head;
	while (current)
	{
		if (ft_strncmp(current->name, str, len))
			return (current->name);
	}
}

char	*smart_copy(char *src)
{
	int		i;
	char	*name;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '$')
		{
			name = loop_check_variable(src, get_variable_length(src));
			if (name)
				
		}
		j++;
		i++;
	}
}

void	expand_quotes(t_lexer_node *node)
{
	t_lexer	*lexer;
	int		i;
	char	*temp;

	i = 0;
	lexer = node->lexer;
	while (i < node->lexer_size)
	{
		if (node->lexer->type == '\'')
		{
			temp = node->lexer->content;
			node->lexer->content = ft_copy_single(temp);
		}
		else if (node->lexer->type == '"')
		{
			temp = node->lexer->content;
			node->lexer->content = smart_copy(temp);
		}
	}
}
