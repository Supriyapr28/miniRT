/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:22:19 by spaipur-          #+#    #+#             */
/*   Updated: 2025/07/31 19:03:32 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	if (!dst && !src)
		return (NULL);
	d = (char *)dst;
	s = (const char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_str_join(char *s1, char *s2, t_join *k)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(sizeof(char) * (k->last_len + k->read_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		if (s1[i] == '\n' && k->nl_idx == -1)
			k->nl_idx = i;
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		if (s2[j] == '\n' && k->nl_idx == -1)
			k->nl_idx = i;
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	k->full_len = i;
	return (str);
}

char	*free_n_ret_null(char **p1, char **p2, char **p3)
{
	if (p1)
	{
		if (*p1)
			free(*p1);
		*p1 = NULL;
	}
	if (p2)
	{
		if (*p2)
			free(*p2);
		*p2 = NULL;
	}
	if (p3)
	{
		if (*p3)
			free(*p3);
		*p3 = NULL;
	}
	return (NULL);
}

void	get_len_n_nl_idx(char *last_buf, int *len, int *nl_idx)
{
	int	index;

	index = 0;
	*len = 0;
	*nl_idx = -1;
	while (last_buf && last_buf[index])
	{
		if (last_buf[index] == '\n' && *nl_idx == -1)
			*nl_idx = index;
		index++;
	}
	*len = index;
}
