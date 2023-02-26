/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:50:47 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/26 22:45:38 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


char	*search_in_path(char *cmd)
{
	char	**path;
	char	*final;
	int		i;

	if (access(cmd, X_OK))
		return (cmd);
	i = 0;
	final = 0;
	path = ft_split(get_variable_cmd("PATH"), ":");
	while (path[i])
	{
		final = ft_strjoin(0, path[i]);
		final = ft_strjoin(final, "/");
		final = ft_strjoin(final, cmd);
		if (access(final, X_OK) == 0)
		{
			tab_free(path);
			return (final);
		}
		free(final);
		i++;
	}
	return (0);
}

int	is_builtin(char *str)
{
	int		slach_index;

	if (str && (ft_strcmp(str, "echo") || ft_strcmp(str, "cd") || ft_strcmp(str, "pwd")
			|| ft_strcmp(str, "export") || ft_strcmp(str, "unset")
				|| ft_strcmp(str, "env") || ft_strcmp(str, "exit")))
		return (1);
	if (access(str, X_OK) == 0)
	{
		slach_index = ft_strrchr(str, '/');
		if (!slach_index)
			return (0);
		str = str + slach_index + 1;
		if (str && (ft_strcmp(str, "echo") || ft_strcmp(str, "cd") || ft_strcmp(str, "pwd")
			|| ft_strcmp(str, "export") || ft_strcmp(str, "unset")
				|| ft_strcmp(str, "env") || ft_strcmp(str, "exit")))
			return (1);
	}
	return (0);
}

void	exec_builtin(char *cmd, char **args)
{
	int	i;
	
	i = ft_strrchr(cmd, '/') + 1;
	if (i == -1)
		i = 0;
	cmd = cmd + i;
	if (ft_strcmp(cmd, "echo"))
		echo_cmd(args);
	if (ft_strcmp(cmd, "cd"))
		cd_cmd(args);
	if (ft_strcmp(cmd, "unset"))
		unset_cmd(args);
	if (ft_strcmp(cmd, "pwd"))
		pwd_cmd();
	if (ft_strcmp(cmd, "exit"))
		exit_cmd(args);
	if (ft_strcmp(cmd, "env"))
		env_cmd('e');
	if (ft_strcmp(cmd, "export"))
		export_cmd(args);
}

void	modifie_variable(char *variable, char *new_value)
{
	t_mini_env	*current;

	current = g_global.env_head;
	while (current)
	{
		if (ft_strcmp(current->name, variable))
		{
			free(current->value);
			if (new_value)
				current->value = ft_strdup(new_value);
			else
				current->value = 0;
			return ;
		}
		current = current->next;
	}
}

char	*get_variable_cmd(char *variable)
{
	t_mini_env	*current;

	current = g_global.env_head;
	while (current)
	{
		if (ft_strcmp(current->name, variable))
			return (current->value);
		current = current->next;
	}
	return (0);
}
