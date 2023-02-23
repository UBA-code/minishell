/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:25:03 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/22 22:10:44 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split(char const *s, char *sep)
{
	char	**final_str;
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	final_str = ft_calloc(sizeof(char *), calc_element(s, sep, &x, &j) + 1);
	if (!final_str || !s)
		return (0);
	get_next_str(s, sep, &i, &j);
	if (i-- == ft_strlen(s))
		return ((char *[1]){NULL});
	while (++i <= ft_strlen(s))
	{
		if (includes(s[i], sep) || s[i] == '\0')
		{
			if (!substr_and_alloc_check(&final_str[x++], s, j, i - j))
				return (free_tab(final_str, --x));
			get_next_str(s, sep, &i, &j);
		}
	}
	return (final_str);
}
