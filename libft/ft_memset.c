/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:44:25 by spaipur-          #+#    #+#             */
/*   Updated: 2025/07/12 13:19:21 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	set_value;
	size_t			i;
	unsigned char	*str;

	i = 0;
	set_value = (unsigned char)c;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = set_value;
		i++;
	}
	return (str);
}
