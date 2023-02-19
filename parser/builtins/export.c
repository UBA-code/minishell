/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:39:02 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/18 11:39:40 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_errors(char *name)
{
	ft_putstr("bash: export: ", STDERR_FILENO);
	ft_putstr(name, STDERR_FILENO);
	free(name);
	ft_putstr(": not a valid identifier\n", STDERR_FILENO);
}

void	loop_export(char *arg)
{
	int			len;
	char		*name;
	char		*value;

	len = ft_strchr(arg, '=');
	if (len == -1)
		len = ft_strlen(arg);
	if (arg[0] == '=')
		return (ft_error("bash: export: `=': not a valid identifier", 1));
	name = get_substring(arg, len);
	if (!check_export_syntax(name))
		return (export_errors(name));
	value = 0;
	if (arg[len])
		value = get_substring(arg + len + 1, ft_strlen(arg + len + 1));
	if (env_search(name))
	{
		modifie_variable(name, value);
		free(name);
		return (free(value));
	}
	env_create_node(name, value);
}

void	export_cmd(char **args)
{
	char		*name;
	char		*value;
	int			len;
	int			i;

	if (!args[1])
	{
		env_cmd('x');
		return ;
	}
	i = 1;
	while (args[i])
	{
		loop_export(args[i]);
		i++;
	}
}