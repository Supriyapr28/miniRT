/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <spaipur-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 12:41:32 by spaipur-          #+#    #+#             */
/*   Updated: 2026/07/20 13:21:22 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft/libft.h"

int	ft_err_handler(t_scene *scene, const char *msg)
{
	free_scene(scene);
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd((char *)msg, 2);
	exit(1);
	return (0);
}

void	parse_error(const char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd((char *)msg, 2);
	exit(1);
}
