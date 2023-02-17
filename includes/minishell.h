/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:46:57 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/17 14:13:27 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../parser/get_next_line/get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "dirent.h"

#define CURRENT_CONDITION str[i] == '\'' || str[i] == '"' || str[i] == '<' || str[i] == '>' \
			|| str[i] == ' ' || str[i] == ')' || str[i] == '('

#define NEXT_CONDITIN str[i + 1] == '\'' || str[i + 1] == '"' || str[i + 1] == '<' || str[i + 1] == '>' \
			|| str[i + 1] == ' ' || str[i + 1] == ')' || str[i + 1] == '('

#define LEFT_REDIRECT ">"
#define RIGHT_REDIRECT "<"
#define DOUBLE_QUOTES "\""
#define SINGLE_QUOTES "'"
#define LEFT_GROUP "("
#define RIGHT_GROUP ")"
#define SPACE " "
#define DOLAR "$"
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
	char *content;
	char type;
} t_lexer;

typedef struct s_files
{
	char *file;
	char type;
	struct s_files *next;
} t_files;

typedef struct s_cmd
{
	char **cmd;
	t_files *files_head;
} t_cmd;

typedef struct s_mini_env
{
	char *name;
	char *value;
	struct s_mini_env *next;
	struct s_mini_env *previous;
} t_mini_env;

typedef struct s_lexer_node
{
	t_lexer *lexer;
	size_t lexer_size;
	t_cmd cmd_struct;
	char **env;
	struct s_lexer_node *next;
} t_lexer_node;

typedef struct s_g_global
{
	t_mini_env *env_head;
	int error;
} t_global;

#ifndef g_global
t_global g_global;
#endif

void			*ft_memset(void *b, int c, size_t len);
void			*ft_calloc(size_t count, size_t size);
void			tab_free(char **tab);
char			**ft_split(char const *s, char *sep);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *str);
void			add_back_lst(t_lexer_node **head, t_lexer_node *node);
void			add_front_lst(t_lexer_node **head, t_lexer_node *node);
void			lst_clear(t_lexer_node **head);
t_files			*files_create_node(t_files **head, char *file, char type);
void			files_add_back_lst(t_files *head, t_files *node);
t_lexer_node	*lexer_create_node(t_lexer_node **head);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(char *s1, char *s2, int n);
void			init_lexer_node(t_lexer_node **head, char *line, char **env);
void			ft_error(char *str, int error);
int				check_quotes(char *str);
void			parser_utils(t_lexer_node **lexer_head);
void			files_add_back_lst(t_files *head, t_files *node);
t_lexer_node	*lexer_create_node(t_lexer_node **head);
void			env_add_back_lst(t_mini_env *head, t_mini_env *node);
t_mini_env		*env_create_node(char *name, char *value);
void			create_env(char **env);
char			*get_variable_cmd(char *variable);
void			env_del_node(char *variable);
void			echo_cmd(char **args);
char			*get_variable_cmd(char *variable);
void			export_cmd(char **args);
void			unset_cmd(char **args);
void			env_cmd(char c);
void			pwd_cmd(void);
void			ft_putstr(char *str, int fd);
int				ft_strchr(char *str, char c);
void			cd_cmd(char **args);
void			modifie_variable(char *variable, char *new_value);
void			free_parser(t_lexer_node *head);
int				get_last_of_var(char *str);
char			*join_string(t_lexer_node *node, int *nb);
char			*smart_get_variable(char *str);
int				check_export_syntax(char *str);
int				env_search(char *variable);
long long		ft_atoi(char *nb);
char			*ft_itoa(int n);

#endif