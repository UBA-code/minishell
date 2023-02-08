/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mini_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:57:42 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/08 10:51:10 by ybel-hac         ###   ########.fr       */
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
	return (0);
}

void	create_env(t_mini_env **head, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		env_create_node(head, ft_substr(env[i], 0, ft_strchr(env[i], '=')),
			ft_substr(env[i], (ft_strchr(env[i], '=') + 1), ft_strlen(env[i])));
		i++;
	}
}
