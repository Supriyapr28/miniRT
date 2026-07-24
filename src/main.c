/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uvadakku <uvadakku@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:03:57 by uvadakku          #+#    #+#             */
/*   Updated: 2026/07/21 12:26:06 by uvadakku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
#include "rt.h"

int create_image(t_mlx *mlx)
{
    mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!mlx->img)
    {
        printf("failed to create an image\n");
        destroy_mlx(mlx);
        return (0);
    }
    mlx->addr = mlx_get_data_addr(
        mlx->img,
        &mlx->bpp,
        &mlx->line_len,
        &mlx->endian
    );
    return (1);
}

void render_color(t_mlx *mlx, int color)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            put_pixel(mlx, x, y, color);
            x++;
        }
        y++;
    }
}

t_mlx *fill_color(t_mlx *mlx)
{
    if (!create_image(mlx))
        return (NULL);
    render_color(mlx, BLUE_COLOR);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    return (mlx);
}

t_mlx  *start_mlx(void)
{
    t_mlx  *mlx;

    mlx = init_mlx();
    if (!mlx)
    {
        printf("failed to initialize the connection with minilibx\n");
        return (NULL);
    }
    mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
    if (!mlx->win)
    {
        printf("failed to create the window\n");
        destroy_mlx(mlx);
        return (NULL);
    }
    if (fill_color(mlx) == NULL)
        return (NULL);
    return (mlx);
}

int main(int argc, char **argv)
{
    t_mlx *mlx;
    t_scene *scene;

    if (argc != 2)
    {
        printf("usage: ./miniRT scenes/scene.rt\n");
        return (1);
    }
    scene = parse_scene(argv[1]);
    if (!scene)
        return (1);
    mlx = start_mlx();
    if (!mlx)
        return (1);
    setup_hooks(mlx);
    mlx_loop(mlx->mlx);
    destroy_mlx(mlx);
    return (0);
}
