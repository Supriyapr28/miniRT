#include "../libft/libft.h"
#include "parse.h"

int ft_err_handler(t_scene *scene, const char *msg)
{

    free_scene(scene);
    ft_putstr_fd("Error: ", 2);
    ft_putendl_fd((char *)msg, 2);
    exit(1);
    return (0);
}
