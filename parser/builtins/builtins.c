/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:57:56 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/16 18:27:19 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_cmd(char **args)
{
	int	i;

	i = 1;
	if (ft_strcmp(args[1], "-n"))
		i = 2;
	while (args[i] && !ft_strcmp(args[i], "-n"))
	{
		if (args[i + 1])
			printf("%s ", args[i]);
		else
			printf("%s", args[i]);
		i++;
	}
	if (!ft_strcmp(args[1], "-n"))
		printf("\n");
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

int	env_search(char *variable)
{
	t_mini_env *current;

	current = g_global.env_head;
	while (current)
	{
		if (ft_strcmp(current->name, variable))
			return (1);
		current = current->next;
	}
	return (0);
}

void	env_cmd(char c)
{
	t_mini_env	*current;

	current = g_global.env_head;
	if (c == 'x')
	{
		while (current)
		{
			if (current->value == 0)
				printf("declare -x %s\n", current->name);
			else
				printf("declare -x %s=\"%s\"\n", current->name, current->value);
			current = current->next;
		}
	}
	else
	{
		while (current)
		{
			if (current->value)
				printf("%s=%s\n", current->name, current->value);
			current = current->next;
		}
	}
}

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
		return (ft_error("bash: export: `=': not a valid identifier", 0));
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

void	unset_cmd(char **args)
{
	if (args[1])
		env_del_node(args[1]);
}

void	exit_cmd()
{
	exit(EXIT_SUCCESS);
}

void	pwd_cmd(void)
{
	printf("%s\n", get_variable_cmd("PWD"));
}

void	cd_cmd(char **args)
{
	int		folder;
	char	*oldpwd;

	if (!args[1])
		chdir("/Users/ybel-hac");
	else if (ft_strcmp(args[1], "-"))
	{
		if (!get_variable_cmd("OLDPWD"))
			ft_error("bash: cd: OLDPWD not set\n", 0); // error need to check
		else
			chdir(get_variable_cmd("OLDPWD"));
	}
	else
	{
		folder = chdir(args[1]);
		if (folder)
		{
			ft_error("bash: ", 0); //need to check error
			ft_error(args[1], 0); //need to check error
			ft_error(": No such directory\n", 0); //need to check error
			return ;
		}
	}
	modifie_variable("OLDPWD", get_variable_cmd("PWD"));
	modifie_variable("PWD", getcwd(0, 0));
}
