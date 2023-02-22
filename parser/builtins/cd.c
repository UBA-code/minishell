/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:44:52 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/21 17:54:04 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_cmd(char **args)
{
	int		folder;
	char	*oldpwd;

	if (!args[1])
	{
		if (chdir("/Users/ybel-hac"))
			ft_error("/Users/ybel-hac: no such file or directory\n", 1);
	}
	else if (ft_strcmp(args[1], "-"))
	{
		if (!get_variable_cmd("OLDPWD"))
			ft_error("bash: cd: OLDPWD not set\n", 1);
		else
			chdir(get_variable_cmd("OLDPWD"));
	}
	else
	{
		folder = chdir(args[1]);
		if (folder)
		{
			ft_error("bash: ", 1);
			ft_error(args[1], 1);
			ft_error(": No such directory\n", 1);
			return ;
		}
	}
	modifie_variable("OLDPWD", get_variable_cmd("PWD"));
	modifie_variable("PWD", getcwd(0, 0));
}
