/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: us <us@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:03:57 by uvadakku          #+#    #+#             */
/*   Updated: 2026/09/01 18:23:30 by us               ###   ########.fr       */
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

static int ray_to_color(const t_ray *ray)
{
    int r;
    int g;
    int b;

    r = (int)((ray->direction.x * 0.5 + 0.5) * 255.0);
    g = (int)((ray->direction.y * 0.5 + 0.5) * 255.0);
    b = (int)((ray->direction.z * 0.5 + 0.5) * 255.0);
    if (r < 0)
        r = 0;
    if (r > 255)
        r = 255;
    if (g < 0)
        g = 0;
    if (g > 255)
        g = 255;
    if (b < 0)
        b = 0;
    if (b > 255)
        b = 255;
    return ((r << 16) | (g << 8) | b);
}

void render_color(t_mlx *mlx, const t_scene *scene)
{
    int x;
    int y;
    t_ray ray;
    int color;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            ray = make_camera_ray(scene, x, y);
            color = ray_to_color(&ray);
            put_pixel(mlx, x, y, color);
            x++;
        }
        y++;
    }
}

t_mlx  *start_mlx(t_app *app)
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
    if (!create_image(mlx))
        return (NULL);
    app->mlx = mlx;
    render_frame(app);
    return (mlx);
}

int main(int argc, char **argv)
{
    t_app app;

    if (argc != 2)
    {
        printf("usage: ./miniRT scenes/scene.rt\n");
        return (1);
    }
    app.mlx = NULL;
    app.scene = parse_scene(argv[1]);
    if (!app.scene)
        return (1);
    if (!start_mlx(&app))
    {
        free_scene(app.scene);
        return (1);
    }
    setup_hooks(&app);
    mlx_loop(app.mlx->mlx);
    destroy_app(&app);
    return (0);
}

