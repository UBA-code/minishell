/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:50:10 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/23 00:02:39 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	includes(char c, char *sep)
{
	int	i;

	i = -1;
	while (sep[++i])
		if (sep[i] == c)
			return (1);
	return (0);
}

int	calc_element(const char *s, char *sep, size_t *x, size_t *j)
{
	size_t	i;
	size_t	len;

	*x = 0;
	*j = 0;
	i = 0;
	len = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!includes(s[i], sep))
			if (includes(s[i + 1], sep) || s[i + 1] == '\0')
				len++;
		i++;
	}
	return (len);
}

void	get_next_str(const char *str, char *sep, size_t *i, size_t *j)
{
	*j = *i;
	while (str[*i])
	{
		if (includes(str[*i], sep))
		{
			++*i;
			++*j;
		}
		else
			break ;
	}
}

int	substr_and_alloc_check(char **final_str, const char *s,
				int j, int len)
{
	*final_str = ft_substr(s, j, len);
	if (!final_str)
		return (0);
	return (1);
}

char	**free_tab(char **tab, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		free(tab[i]);
		i++;
	}
	return (NULL);
}

