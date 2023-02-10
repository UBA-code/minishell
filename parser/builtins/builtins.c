/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:57:56 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/10 21:22:54 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_cmd(char *msg, int option)
{
	if (option)
		printf("%s", msg);
	else
		printf("%s\n", msg);
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

void	export_cmd(t_mini_env **head, char *str)
{
	int			i;
	char		*name;
	char		*value;

	i = -1;
	if (!str)
	{
		env_cmd('x');
		return ;
	}
	while (str[++i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| (str[i] == '_') || str[i] == '='))
		{
			ft_putstr("bash: export: ", STDERR_FILENO);
			ft_putstr(str, STDERR_FILENO);
			ft_putstr(": not a valid identifier\n", STDERR_FILENO);
			return ; // need to check error code
		}
	}
	name = get_substring(str, i);
	value = 0;
	if (str[i] && !(++i))
		value = get_substring(str + i, ft_strlen(str + i));
	env_create_node(head, name, value);
}

void	unset_cmd(t_mini_env **head, char *variable)
{
	env_del_node(head, variable);
}

void	exit_cmd()
{
	exit(EXIT_SUCCESS);
}

void	pwd_cmd(t_mini_env *head)
{
	while (head)
	{
		if (ft_strcmp(head->name, "PWD"))
		{
			printf("%s\n", head->value);
			return ;
		}
		head = head->next;
	}
}

void	cd_cmd(char *dir)
{
	int		folder;
	char	*oldpwd;

	if (!dir)
		chdir("/Users/ybel-hac");
	else if (ft_strcmp(dir, "-"))
	{
		if (!get_variable_cmd("OLDPWD"))
			ft_error("bash: cd: OLDPWD not set\n", 0); // error need to check
		else
			chdir(get_variable_cmd("OLDPWD"));
	}
	else
	{
		folder = chdir(dir);
		if (folder)
		{
			ft_error("bash: ", 0); //need to check error
			ft_error(dir, 0); //need to check error
			ft_error(": No such directory\n", 0); //need to check error
			return ;
		}
		modifie_variable("OLDPWD", get_variable_cmd("PWD"));
		modifie_variable("PWD", getcwd(0, 0));
	}
}
