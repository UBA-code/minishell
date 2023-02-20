/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybel-hac <ybel-hac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:25:57 by ybel-hac          #+#    #+#             */
/*   Updated: 2023/02/20 16:22:04 by ybel-hac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_error_free(t_lexer_node *lexer_head)
{
	lst_clear(&lexer_head);
	ft_error("Error, Parse Error\n", 258);
}
