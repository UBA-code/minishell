/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:43:48 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/04 16:07:58 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pwd_cmd(void)
{
	char	*temp;

	temp = getcwd(0, 0);
	if (!temp)
		printf("%s\n", get_variable_cmd("PWD"));
	else
		printf("%s\n", temp);
	free(temp);
}
