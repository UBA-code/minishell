/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:43:48 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/21 15:55:20 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_cmd(void)
{
	if (env_search("PWD"))
		printf("%s\n", get_variable_cmd("PWD"));
	else
		printf("%s\n", getcwd(0, 0));
}
