/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:16:41 by spaipur-          #+#    #+#             */
/*   Updated: 2025/08/05 11:35:33 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_result
{
	int		return_line;
	char	*line;
}	t_result;

typedef struct s_join
{
	int	last_len;
	int	read_len;
	int	nl_idx;
	int	full_len;
}	t_join;

char	*get_next_line(int fd);
char	*free_n_ret_null(char **p1, char **p2, char **p3);
char	*ft_str_join(char *s1, char *s2, t_join *j);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	get_len_n_nl_idx(char *last_buf, int *len, int *nl_idx);

#endif