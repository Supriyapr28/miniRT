/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:10:59 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/16 12:55:46 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int handle_key(int keycode, t_mlx *mlx)
{
    if (keycode == 53 || keycode == 65307)
    {
        destroy_mlx(mlx);
        exit(0);
    }
    return (0);
}

int handle_close(t_mlx *mlx)
{
    destroy_mlx(mlx);
    exit(0);
    return (0);
}

void setup_hooks(t_mlx * mlx)
{
    mlx_hook(mlx->win, 2, 1L << 0, handle_key, mlx); //key press initiated
    mlx_hook(mlx->win, 17, 0, handle_close, mlx);
}
