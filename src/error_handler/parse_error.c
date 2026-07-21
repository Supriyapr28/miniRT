#include "../libft/libft.h"

void parse_error(const char *msg)
{
    ft_putstr_fd("Error: ", 2);
    ft_putendl_fd((char *)msg, 2);
    exit(1);
}
