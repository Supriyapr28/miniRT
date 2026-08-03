/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:00:44 by spaipur-          #+#    #+#             */
/*   Updated: 2025/08/05 16:12:44 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_ln(char **src, int nl_idx, char *last, int last_len)
{
	char	*line;

	line = (char *)malloc(sizeof(char) * (nl_idx + 2));
	if (!line)
		return (NULL);
	if (nl_idx >= 1)
		ft_memcpy(line, *src, nl_idx);
	line[nl_idx] = '\n';
	line[nl_idx + 1] = '\0';
	if (last_len > 0)
	{
		ft_memcpy(last, &((*src)[nl_idx + 1]), last_len);
		last[last_len] = '\0';
		return (line);
	}
	last[0] = '\0';
	return (line);
}

static char	*handle_eof(char **buf, char *last, int len, char *cur_buf)
{
	char	*line;
	int		nl_idx;

	free(cur_buf);
	nl_idx = 0;
	if (!*buf || !**buf)
		return (free_n_ret_null(buf, NULL, NULL));
	while ((*buf)[nl_idx])
	{
		if ((*buf)[nl_idx] == '\n')
		{
			line = get_ln(buf, nl_idx, last, len - nl_idx - 1);
			*buf = free_n_ret_null(buf, NULL, NULL);
			return (line);
		}
		nl_idx++;
	}
	line = *buf;
	*buf = NULL;
	last[0] = '\0';
	return (line);
}

static t_result	handle_new_data(char **temp, char *last, char *curr_buffer,
	t_join *j)
{
	char		*str;
	t_result	res;

	res.return_line = 1;
	res.line = NULL;
	j->nl_idx = -1;
	str = ft_str_join(*temp, curr_buffer, j);
	if (!str)
	{
		*temp = free_n_ret_null(&curr_buffer, temp, NULL);
		last[0] = '\0';
		return (res);
	}
	*temp = free_n_ret_null(temp, NULL, NULL);
	last[0] = '\0';
	if (j->nl_idx != -1)
	{
		free(curr_buffer);
		res.line = get_ln(&str, j->nl_idx, last, j->full_len - j->nl_idx - 1);
		str = free_n_ret_null(&str, NULL, NULL);
		return (res);
	}
	res.return_line = 0;
	*temp = str;
	return (res);
}

static char	*read_from_file(int fd, char **temp, char *last, t_join *j)
{
	char		*curr_buffer;
	t_result	res;

	res.line = NULL;
	curr_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!curr_buffer)
		return (free_n_ret_null(temp, NULL, NULL));
	while (1)
	{
		j->read_len = read(fd, curr_buffer, BUFFER_SIZE);
		if (j->read_len < 0)
		{
			last[0] = '\0';
			return (free_n_ret_null(temp, &curr_buffer, NULL));
		}
		else if (j->read_len == 0)
			return (handle_eof(temp, last, j->last_len, curr_buffer));
		curr_buffer[j->read_len] = '\0';
		res = handle_new_data(temp, last, curr_buffer, j);
		if (res.return_line == 1)
			return (res.line);
		j->last_len = j->full_len;
	}
}

char	*get_next_line(int fd)
{
	static char	last[BUFFER_SIZE + 1];
	char		*temp;
	char		*line;
	t_join		j;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	get_len_n_nl_idx(last, &j.last_len, &j.nl_idx);
	j.read_len = 0;
	temp = (char *)malloc(sizeof(char) * j.last_len + 1);
	if (!temp)
	{
		last[0] = '\0';
		return (NULL);
	}
	if (j.last_len > 0)
		ft_memcpy(temp, last, j.last_len);
	temp[j.last_len] = '\0';
	if (j.nl_idx != -1)
	{
		line = get_ln(&temp, j.nl_idx, last, (j.last_len - j.nl_idx - 1));
		temp = free_n_ret_null(&temp, NULL, NULL);
		return (line);
	}
	return (read_from_file(fd, &temp, last, &j));
}
