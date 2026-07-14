#include "libft.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./miniRT scene.rt", 2);
		return (1);
	}
	return (0);
}
