/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:46:57 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/25 00:49:37 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <string.h>

# define LEFT_REDIRECT ">"
# define RIGHT_REDIRECT "<"
# define DOUBLE_QUOTES "\""
# define SINGLE_QUOTES "'"
# define LEFT_GROUP "("
# define RIGHT_GROUP ")"
# define SPACE " "
# define DOLAR "$"
// #define equal "="

typedef struct s_get_variable_struct
{
	char	*variable;
	char	*temp;
	char	*final;
	int		i;
	char	*string;
}	t_get_variable_struct;

typedef struct lexer_s
{
	char	*content;
	char	type;
}	t_lexer;


typedef struct s_files
{
	char			*file;
	char			type;
	struct s_files	*next;
}	t_files;

typedef struct s_cmd
{
	char	**cmd;
	t_files	*files_head;
}	t_cmd;

typedef struct s_mini_env
{
	char				*name;
	char				*value;
	struct s_mini_env	*next;
	struct s_mini_env	*previous;
}	t_mini_env;

typedef struct s_lexer_node
{
	t_lexer				*lexer;
	int					lexer_size;
	t_cmd				cmd_struct;
	char				**env;
	struct s_lexer_node	*next;
}	t_lexer_node;

typedef t_lexer_node	t_executor;

typedef struct s_g_global
{
	t_mini_env	*env_head;
	int			error;
}	t_global;

# ifndef G_GLOBAL

t_global	g_global;

# endif

void	modifie_variable(char *variable, char *new_value);
char	*get_variable_cmd(char *variable);
void	cd_cmd(char **args);
void	echo_utils(char **args, int neww);
void	echo_cmd(char **args);
int	env_search(char *variable);
void	env_cmd(char c);
void	exit_cmd(char **args);
void	export_errors(char *name);
void	loop_export(char *arg);
void	export_cmd(char **args);
void	pwd_cmd(void);
void	unset_cmd(char **args);
void	parse_error_free(t_lexer_node *lexer_head);
int	lexer_check(char c);
int	get_next_word(char *str, int i);
int	get_token_len(char *str);
int	get_token_size(char *str, int *num);
char	get_type(char *content);
void	init_lexer_node(t_lexer_node **head, char *line, char **env);
void	add_back_lst(t_lexer_node **head, t_lexer_node *node);
void	files_add_back_lst(t_files	*head, t_files *node);
void	env_add_back_lst(t_mini_env	*head, t_mini_env *node);
void	add_front_lst(t_lexer_node **head, t_lexer_node *node);
t_lexer_node	*lexer_create_node(t_lexer_node **head);
t_files	*files_create_node(t_files **head, char *file, char type);
t_mini_env	*env_create_node(char *name, char *value);
void	env_del_node(char *variable);
void	lst_clear(t_lexer_node **head);
size_t	lst_size(t_lexer_node *lst);
char	*smart_get_variable(char *str);
char	*single_expand(t_lexer_node *node, int *nb);
char	*double_expand(t_lexer_node *node, int *nb);
char	*join_string(t_lexer_node *node, int *nb);
int	check_export_syntax(char *str);
int	get_last_of_var(char *str);
int	get_dolar(char *str);
char	*strjoin_small(char *s1, char c);
int	dolar_work(t_get_variable_struct *utils);
int	speciale_check(char c, int *i);
void	free_parser(t_lexer_node *head);
void	skip_files(t_lexer_node *node, int *i);
int	parser_get_size(t_lexer_node *node);
char	get_file_type(t_lexer_node *node, int i);
int	get_after_file(t_lexer_node *node, int i);
int	parser_work(t_lexer_node *node);
char	*get_cmd_path(char *cmd);
int	parser_utils(t_lexer_node **lexer_head);
void	create_env(char **env);
int	check_dbquotes(char *str, int *i, int j);
int	check_squotes(char *str, int *i, int j);
int	check_quotes(char *str);
void	ft_error(char *str, int error);



// void			add_back_lst(t_lexer_node **head, t_lexer_node *node);
// void			add_front_lst(t_lexer_node **head, t_lexer_node *node);
// void			lst_clear(t_lexer_node **head);
// t_files			*files_create_node(t_files **head, char *file, char type);
// void			files_add_back_lst(t_files *head, t_files *node);
// t_lexer_node	*lexer_create_node(t_lexer_node **head);
// void			init_lexer_node(t_lexer_node **head, char *line, char **env);
// void			init_lexer_node(t_lexer_node **head, char *line, char **env);
// void			ft_error(char *str, int error);
// int				check_quotes(char *str);
// int				parser_utils(t_lexer_node **lexer_head);
// void			files_add_back_lst(t_files *head, t_files *node);
// t_lexer_node	*lexer_create_node(t_lexer_node **head);
// void			env_add_back_lst(t_mini_env *head, t_mini_env *node);
// t_mini_env		*env_create_node(char *name, char *value);
// void			create_env(char **env);
// char			*get_variable_cmd(char *variable);
// void			env_del_node(char *variable);
// void			echo_cmd(char **args);
// char			*get_variable_cmd(char *variable);
// void			export_cmd(char **args);
// void			unset_cmd(char **args);
// void			env_cmd(char c);
// void			pwd_cmd(void);
// void			ft_putstr(char *str, int fd);
// void			cd_cmd(char **args);
// void			modifie_variable(char *variable, char *new_value);
// void			free_parser(t_lexer_node *head);
// int				get_last_of_var(char *str);
// char			*join_string(t_lexer_node *node, int *nb);
// char			*smart_get_variable(char *str);
// int				check_export_syntax(char *str);
// int				env_search(char *variable);
// int				get_last_of_var(char *str);
// int				get_dolar(char *str);
// char			*strjoin_small(char *s1, char c);
// int				dolar_work(t_get_variable_struct *utils);
// int				speciale_check(char c, int *i);
// void			skip_files(t_lexer_node *node, int *i);
// int				parser_get_size(t_lexer_node *node);
// char			get_file_type(t_lexer_node *node, int i);
// int				get_after_file(t_lexer_node *node, int i);
// int				lexer_check(char c);
// int				get_next_word(char *str, int i);
// int				get_token_len(char *str);
// int				get_token_size(char *str, int *num);
// char			get_type(char *content);
// void			parse_error_free(t_lexer_node *lexer_head);

// !execution

// int				exec_fun(t_lexer_node *head);
void			rl_replace_line(const char *, int);
#endif