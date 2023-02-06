/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:46:57 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/06 10:53:02 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../parser/get_next_line/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"

# define CURRENT_CONDITION str[i] == '"' || str[i] == '\'' || str[i] == '<' || str[i] == '>' || str[i] == ' ' || str[i] == ')' || str[i] == '('

# define NEXT_CONDITIN str[i + 1] == '"' || str[i + 1] == '\'' || str[i + 1] == '<' || str[i + 1] == '>' || str[i + 1] == ' ' || str[i + 1] == ')' || str[i + 1] == '('

# define LEFT_REDIRECT ">"
# define RIGHT_REDIRECT "<"
# define DOUBLE_QUOTES "\""
# define SINGLE_QUOTES "'"
# define LEFT_GROUP "("
# define RIGHT_GROUP ")"
# define SPACE " "
# define DOLAR "$"

typedef struct lexer_s
{
	char type;
	char *content;
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
	t_files *files_head;
}	t_cmd;

typedef struct s_lexer_node
{
	t_lexer				*lexer;
	size_t				lexer_size;
	t_cmd				cmd_struct;
	char				**env;
	char				*pipe;
	int					loop;
	struct s_lexer_node *next;
}	t_lexer_node;


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
void			files_add_back_lst(t_files	*head, t_files *node);
t_lexer_node	*lexer_create_node(t_lexer_node **head);
int 			ft_strcmp(char *s1, char *s2);
int	ft_strncmp(char *s1, char *s2, int n);
void 			init_lexer_node(t_lexer_node **head, char *line, char **env);
int 			ft_error(char *str, int error);
int 			check_quotes(char *str);
void			parser_utils(t_lexer_node **lexer_head);

#endif