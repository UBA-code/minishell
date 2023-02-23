/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:02:21 by bahbibe           #+#    #+#             */
/*   Updated: 2023/02/23 00:38:56 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <strings.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_is_space(int c);
char	*ft_itoa(int n);
void	*ft_memset(void *b, int c, size_t len);
char	**ft_split(char const *s, char *sep);
int		ft_strchr(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strncpy(char *dest, char *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_tab_free(char **tab);
int		includes(char c, char *sep);
char	**free_tab(char **tab, int x);
int		calc_element(const char *s, char *sep, size_t *x, size_t *j);
void	get_next_str(const char *str, char *sep, size_t *i, size_t *j);
int		substr_and_alloc_check(char **final_str, const char *s, int j, int len);
void	ft_putstr(char *str, int fd);

#endif