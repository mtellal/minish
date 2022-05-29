#include <unistd.h>
#include "input.h"

void    ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		ft_putendl_fd(cwd, 1);
	exit(EXIT_SUCCESS);
}
