/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:52:24 by spaipur-          #+#    #+#             */
/*   Updated: 2025/07/10 15:21:09 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
bzero function is not included by default in the GNU C Library (glibc).
To test them against the system standard, you may need to include
<bsd/string.h> and compile with the -lbsd flag.
*/
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
