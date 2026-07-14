/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:15:15 by spaipur-          #+#    #+#             */
/*   Updated: 2025/07/14 12:42:12 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (NULL);
}

static int	ft_countwords(const char *str, char delimiter)
{
	int	i;
	int	is_word;
	int	wrd_cnt;

	i = 0;
	is_word = 0;
	wrd_cnt = 0;
	while (str[i])
	{
		if (str[i] == delimiter)
			is_word = 0;
		else if (str[i] != delimiter && is_word == 0)
		{
			is_word = 1;
			wrd_cnt++;
		}
		i++;
	}
	return (wrd_cnt);
}

static char	*ft_putword(const char *s, char c, int start)
{
	char	*word;
	int		end;
	int		i;

	end = start;
	while (s[end] && s[end] != c)
		end++;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_split_words(const char *s, char c, char **split, int cnt_words)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (word < cnt_words)
	{
		while (s[i] && s[i] == c)
			i++;
		split[word] = ft_putword(s, c, i);
		if (!split[word])
			return (free_array(split, word));
		while (s[i] && s[i] != c)
			i++;
		word++;
	}
	split[word] = NULL;
	return (split);
}

char	**ft_split(const char *s, char c)
{
	int		count;
	char	**splitwords;

	if (!s)
		return (NULL);
	count = ft_countwords(s, c);
	splitwords = (char **)malloc(sizeof(char *) * (count + 1));
	if (!splitwords)
		return (NULL);
	return (ft_split_words(s, c, splitwords, count));
}
