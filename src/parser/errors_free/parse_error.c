/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:25:57 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/03/02 21:53:57 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	parse_error_free(t_lexer_node *lexer_head, int n)
{
	int	i;

	i = -1;
	while (lexer_head->cmd_struct.cmd[++i])
		free(lexer_head->cmd_struct.cmd[i]);
	lst_clear(&lexer_head);
	free(lexer_head->cmd_struct.cmd);
	if (n)
		ft_error("Error, Parse Error\n", 258);
}
