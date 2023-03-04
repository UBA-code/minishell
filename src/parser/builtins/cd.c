/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:44:52 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/04 16:07:30 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	cd_utils(char *str)
{
	ft_error("bash: ", 1);
	ft_error(str, 1);
	ft_error(": No such directory\n", 1);
}

int	cd_work(char **args)
{
	int	folder;

	if (!args[1])
	{
		if (chdir(get_variable_cmd("HOME")))
			ft_error("bash: cd: HOME not set\n", 1);
	}
	else if (ft_strcmp(args[1], "-"))
	{
		if (!get_variable_cmd("OLDPWD"))
			ft_error("bash: cd: OLDPWD not set\n", 1);
		else
		{
			chdir(get_variable_cmd("OLDPWD"));
			exec_builtin("pwd", (char *[1]){"pwd"});
		}
	}
	else
	{
		folder = chdir(args[1]);
		if (folder)
			return (cd_utils(args[1]), 0);
	}
	return (1);
}

void	cd_cmd(char **args)
{
	char	*temp;

	if (!cd_work(args))
		return ;
	modifie_variable("OLDPWD", get_variable_cmd("PWD"));
	temp = getcwd(0, 0);
	if (!temp)
	{
		perror("cd: error retrieving current \
		directory: getcwd: cannot access parent directories");
		temp = ft_strjoin(0, get_variable_cmd("PWD"));
		temp = ft_strjoin(temp, "..");
		modifie_variable("PWD", temp);
	}
	else
		modifie_variable("PWD", temp);
	free(temp);
}
