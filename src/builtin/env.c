#include "input.h"

void	ft_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->var, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env->content, 1);
		env = env->next;
	}
}
