/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mini_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:57:42 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/22 22:56:45 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	create_env(char **env)
{
	int		i;
	char	*value;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=') == -1)
			value = 0;
		else
			value = ft_substr(env[i],
					(ft_strchr(env[i], '=') + 1), ft_strlen(env[i]));
		env_create_node(ft_substr(env[i], 0, ft_strchr(env[i], '=')),
			value);
		i++;
	}
}
