/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:20:07 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/22 22:10:04 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str_alloc;

	if (size && count >= (SIZE_MAX / size))
		return (0);
	str_alloc = malloc(count * size);
	if (!str_alloc)
		return ((void *)0);
	ft_memset(str_alloc, '\0', count * size);
	return (str_alloc);
}
