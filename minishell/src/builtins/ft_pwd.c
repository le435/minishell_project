
#include "../minishell.h"


int	ft_pwd(t_env *env)
{
	char	*cwd;
	t_env   *pwd_node;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		
		return (free(cwd), 0);
	}
	pwd_node = ft_check_var("PWD", env);
    if (pwd_node && pwd_node->value) 
    {
        ft_putstr_fd(pwd_node->value, 1);
    	ft_putstr_fd("\n", 1);
    }
	else if (env->pwd && env->pwd[0])
	{
		ft_putstr_fd(env->pwd, 1);
		ft_putstr_fd("\n", 1);
		return 0;
	}
	else 
		ft_putstr_fd("pwd: error retrieving current directory\n", 2);
	return (1);
}



















// int	ft_pwd(t_env *env)
// {
// 	char	*cwd;
// 	t_env   *pwd_node;

// 	cwd = getcwd(NULL, 0);
// 	if (cwd)
// 	{
// 		ft_putstr_fd(cwd, 1);
// 		ft_putstr_fd("\n", 1);
		
// 		return (free(cwd), 0);
// 	}
// 	pwd_node = ft_check_var("PWD", env);
//     if (pwd_node && pwd_node->value) 
//     {
//         ft_putstr_fd(pwd_node->value, 1);
//     	ft_putstr_fd("\n", 1);
//     }
// 	else if (env->pwd && env->pwd[0])
// 	{
// 		ft_putstr_fd(env->pwd, 1);
// 		ft_putstr_fd("\n", 1);
// 		return 0;
// 	}
// 	else 
// 		ft_putstr_fd("pwd: error retrieving current directory\n", 2);
// 	return (1);
// }
