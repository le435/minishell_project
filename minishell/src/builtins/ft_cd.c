
#include "../minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	size_t	j;
	char	*dup;

	i = 0;
	while (s[i] && i < n)
		i++;
	dup = malloc(i + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dup[j] = s[j];
		j++;
	}
	dup[i] = '\0';
	return (dup);
}

t_env	*ft_check_var(char *str, t_env *env)
{
	if (!str || !env)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			return (env);
		env = env->next;
	}
	return (NULL);
}

/*
 * update_pwd - Updates the PWD environment variable.
 * @env: Pointer to the head of the environment variables linked list.
 * @new_path: The new path to set for PWD.
 *
 * This function updates the PWD environment variable with the new path.
 * It handles both existing PWD and creating it if it doesn't exist.
 */
static void update_pwd(t_env **env, const char *new_path)
{
    t_env   *pwd_node;
    char    *val_dup;
    char    *pwd_dup;
    char    *pp;

    if (!new_path)
        return;
    pwd_node = ft_check_var("PWD", *env);
    val_dup = ft_strdup(new_path);
    pwd_dup = ft_strdup(new_path);
        if (!val_dup || !pwd_dup)   
    {
        free(val_dup);
        free(pwd_dup);
        return;
    }
    if (pwd_node)
    {
        free(pwd_node->value);
        free(pwd_node->pwd);
        pwd_node->value = val_dup;
        pwd_node->pwd = pwd_dup;
    }
    else
    {
        pp = ft_strdup("PWD");
        if (!pp)
        {
            free(val_dup);
            free(pwd_dup);
            return;
        }
        pwd_node = creat_env(pp, val_dup);
        if (pwd_node)
        {

            free(pwd_node->pwd);
            pwd_node->pwd = pwd_dup;
            add_back_env(env, pwd_node);
            free(val_dup);
        }
        else
        {
            free(val_dup);
            free(pwd_dup);
            free(pp);
        } 
    }
}

static void update_oldpwd(t_env **env, const char *old_path)
{
    t_env   *oldpwd_node;
    char    *path_dup;
    // char    *old;
    
   
    if (!old_path)
        return;
    oldpwd_node = ft_check_var("OLDPWD", *env);
    path_dup = ft_strdup(old_path);
    
    if (!path_dup)
        return;
    if (oldpwd_node)
    {
        free(oldpwd_node->value);
        oldpwd_node->value = path_dup;
    }
    else
    {
        oldpwd_node = creat_env(ft_strdup("OLDPWD"), path_dup);
        if (oldpwd_node)
            add_back_env(env, oldpwd_node);
        else
            free(path_dup);
    }
}

static void handle_chdir_fail(char *path, int *stat)
{
    ft_putstr_fd("minishell: cd: ", 2);
    ft_putstr_fd(path, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    *stat = 1;
}

void check_dir(char    *new_dir,  t_env **env, int *stat, char    *current_pwd_shell)
{
    if (new_dir)
    {
        update_pwd(env, new_dir);
        free((*env)->pwd);
        (*env)->pwd = ft_strdup(new_dir);
        if (!(*env)->pwd)
            *stat = 1;

    }
    else 
        *stat = 1;
    free(current_pwd_shell);
    free(new_dir);
}  
void take_path( char    *current_pwd_shell, char    *new_dir)
{
     char *last_slash = ft_strrchr(current_pwd_shell, '/');
    if (!last_slash || last_slash == current_pwd_shell)
        new_dir = ft_strdup("/");
    else
    {
        new_dir = ft_strndup(current_pwd_shell, last_slash - current_pwd_shell);
        if (new_dir[0] == '\0')
        {
            free(new_dir);
            new_dir = ft_strdup("/");
        }
    }
}


void    ft_cd(char **args, t_env **env, int *stat)
{
    char    *path;
    char    *current_pwd_shell;
    char    *new_dir;
    int     flag;
    char    *s;
    flag = 0;
    *stat = 0;
    new_dir = NULL;
    
    if (!args[1] || args[1][0] == '\0')
    {
        ft_putstr_fd("cd: error retrieving current directory\n", 2);
        *stat = 1;
        return;
    }
    path = args[1];
    // if (!(*env) || !(*env)->pwd)
    // {
    //     *stat = 1;
    //     return;
    // }
    current_pwd_shell = ft_strdup((*env)->pwd);
    if (!current_pwd_shell)
    {
        *stat = 1;
        return;
    }
    if (chdir(path) == -1)
    {
        if (ft_strcmp(path, "..") == 0)
        {
            take_path(current_pwd_shell, new_dir);
            flag = 1; 
            if (chdir(new_dir) == -1) 
                return (handle_chdir_fail(path, stat),free(current_pwd_shell), free(new_dir),(void)0);
        }
        else
        {
            handle_chdir_fail(path, stat);
            free(current_pwd_shell);
            return ;
        }
    }
    update_oldpwd(env, current_pwd_shell);
    if (flag == 0)
    {
        new_dir = getcwd(NULL, 0);
        if (!new_dir)
        {
            ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: \n", 2);
            s = ft_strjoin(current_pwd_shell, "/..");
            if (!s)
                return (free(current_pwd_shell), *stat = 1, (void)0);
            new_dir = s;
        }
    }
    check_dir(new_dir, env, stat,current_pwd_shell);
}



























































































































































































































































































































































































// #include "../minishell.h"

// char	*ft_strndup(const char *s, size_t n)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*dup;

// 	i = 0;
// 	while (s[i] && i < n)
// 		i++;
// 	dup = malloc(i + 1);
// 	if (!dup)
// 		return (NULL);
// 	j = 0;
// 	while (j < i)
// 	{
// 		dup[j] = s[j];
// 		j++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }

// t_env	*ft_check_var(char *str, t_env *env)
// {
// 	if (!str || !env)
// 		return (NULL);
// 	while (env)
// 	{
// 		if (!ft_strcmp(env->key, str))
// 			return (env);
// 		env = env->next;
// 	}
// 	return (NULL);
// }

// static void update_pwd(t_env **env, const char *new_path)
// {
//     t_env   *pwd_node;
//     char    *val_dup;
//     char    *pwd_dup;
//     char     *pp;
    
//     if (!new_path)
//         return;
//     (1) && (pwd_node = ft_check_var("PWD", *env), val_dup
//         = ft_strdup(new_path), pwd_dup = ft_strdup(new_path));
//     if (!val_dup || !pwd_dup)   
//         return ( free(val_dup), free(pwd_dup), (void)0);
//     if (pwd_node)
//         (1) && (free(pwd_node->value), free(pwd_node->pwd),
//             pwd_node->value = val_dup, pwd_node->pwd = pwd_dup);
//     else
//     {
//         (1) && (pp = ft_strdup("PWD"), pwd_node = creat_env(pp, val_dup));
//         if (pwd_node)
//         {
//             (1) && (free(pwd_node->pwd), pwd_node->pwd = pwd_dup);
//             add_back_env(env, pwd_node);
//             free(val_dup);
//         }
//         else
//         {
//             free(val_dup);
//             free(pwd_dup);
//         } 
//         free(pp);
//     }
// }


// static void update_oldpwd(t_env **env, const char *old_path)
// {
//     t_env   *oldpwd_node;
//     char    *path_dup;

//     if (!old_path)
//         return;
//     oldpwd_node = ft_check_var("OLDPWD", *env);
//     path_dup = ft_strdup(old_path);
//     if (!path_dup)
//         return;
//     if (oldpwd_node)
//     {
//         free(oldpwd_node->value);
//         oldpwd_node->value = path_dup;
//     }
//     else
//     {
//         oldpwd_node = creat_env(ft_strdup("OLDPWD"), path_dup);
//         if (oldpwd_node)
//             add_back_env(env, oldpwd_node);
//         else
//             free(path_dup);
//     }
// }

// static void handle_chdir_fail(char *path, int *stat)
// {
//     ft_putstr_fd("minishell: cd: ", 2);
//     ft_putstr_fd(path, 2);
//     ft_putstr_fd(": ", 2);
//     ft_putstr_fd(strerror(errno), 2);
//     ft_putstr_fd("\n", 2);
//     *stat = 1;
// }


// static char *resolve_path_manually(const char *current, const char *target)
// {
//     char    *new_path;
//     char    *temp;

//     if (target[0] == '/')
//         return (ft_strdup(target));
//     if (ft_strcmp(target, "..") == 0)
//     {
//         char    *last_slash;

//         last_slash = ft_strrchr(current, '/');
//         if (last_slash && last_slash != current)
//             return (ft_substr(current, 0, last_slash - current));
//         return (ft_strdup("/"));
//     }
//     temp = ft_strjoin(current, "/");
//     if (!temp)
//         return (NULL);
//     new_path = ft_strjoin(temp, target);
//     free(temp);
//     return (new_path);
// }

// void    ft_cd(char **args, t_env **env, int *stat)
// {
//     char    *path;
//     char    *current_pwd;
//     char        *new_dir = NULL; 
//     t_env   *pwd_node;
//     int     flag = 0; 
    
//     *stat = 0;
//     if (!args[1] || args[1][0] == '\0')
//     {
//      	printf("cd with only a relative or absolute path\n");
//         *stat = 1;
//         return;
//     }
//     path = args[1];
//     current_pwd = getcwd(NULL, 0);
//     if (!current_pwd)
//     {

//         pwd_node = ft_check_var("PWD", *env);
//         if (pwd_node && pwd_node->pwd)
//             current_pwd = ft_strdup(pwd_node->pwd);
//         else
//         {
//             ft_putstr_fd("cd: error retrieving current directory\n", 2);
//             *stat = 1;
//             return;
//         }
//     }
//     if (chdir(path) == -1)
//     {
//         if (ft_strcmp(path, "..") == 0)
//         {
//             char *last_slash = ft_strrchr(current_pwd, '/');
//             if (!last_slash || last_slash == current_pwd)
//                 new_dir = ft_strdup("/");
//             else
//             {
//                 new_dir = ft_strndup(current_pwd, last_slash - current_pwd);
//                 if (new_dir[0] == '\0')
//                 {
//                     free(new_dir);
//                     new_dir = ft_strdup("/");
//                 }
//             }
//             flag = 1;
//             if (chdir(new_dir) == -1)
//             {
//                 handle_chdir_fail(path, stat);
//                 free(current_pwd);
//                 free(new_dir);
//                 return ;
//             }
//         }
//         else
//         {
//             handle_chdir_fail(path, stat);
//             free(current_pwd);
//             return ;
//         }
//     }
//     update_oldpwd(env, current_pwd);
//     if (flag == 0)
//     {
//         new_dir = getcwd(NULL, 0);
//         if (!new_dir)
//         {
//             ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories\n", 2);
//             new_dir = resolve_path_manually(current_pwd, path);
//         }
//     }
//     if (new_dir)
//         update_pwd(env, new_dir);
//     free(current_pwd);
//     free(new_dir);
//     *stat = 0;
// }

