/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:40:40 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/25 11:21:04 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	unset_cmd(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (env_search(args[i]))
			env_del_node(args[i]);
		i++;
	}
}
