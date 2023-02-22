/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:48:04 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/22 22:11:26 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*final_str;
	size_t	real_len;

	if (!s)
		return (0);
	if (len > ft_strlen(s))
		real_len = ft_strlen(s);
	else
		real_len = len;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	final_str = malloc(sizeof(char ) * real_len + 1);
	if (!final_str)
		return (0);
	ft_strncpy(final_str, (char *) s + start, len);
	return (final_str);
}
