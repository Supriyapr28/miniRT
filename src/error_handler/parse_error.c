#include "../libft/libft.h"
#include "parse.h"

void parse_error(const char *msg)
{
    ft_putstr_fd("Error: ", 2);
    ft_putendl_fd((char *)msg, 2);
    exit(1);
}

int ft_err_handler(t_scene *scene, const char *msg)
{
    parse_error(msg);
    free_scene(scene);
    return (0);
}
