/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mini_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:57:42 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/10 15:58:57 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	create_env(t_mini_env **head, char **env)
{
	int	i;
	char *value;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=') == -1)
			value = 0;
		else
			value = ft_substr(env[i], (ft_strchr(env[i], '=') + 1), ft_strlen(env[i]));
		env_create_node(head, ft_substr(env[i], 0, ft_strchr(env[i], '=')),
			value);
		i++;
	}
}
