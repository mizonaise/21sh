/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_buil_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:29:59 by hastid            #+#    #+#             */
/*   Updated: 2019/12/08 23:29:59 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	change_dir(char *dir, t_env **env)
{
	char	*pwd;

	if ((pwd = getcwd(0, 0)))
	{
		add_elem(env, "OLDPWD", pwd);
		ft_memdel((void **)&pwd);
	}
	else if ((pwd = ft_getenv(*env, "PWD")))
		add_elem(env, "OLDPWD", pwd);
	chdir(dir);
	if ((pwd = getcwd(0, 0)))
	{
		add_elem(env, "PWD", pwd);
		ft_memdel((void **)&pwd);
	}
	return (0);
}

int			built_cd(char **args, t_env **env)
{
	char	*dir;

	if (args[1])
	{
		dir = args[1];
		if (!ft_strcmp("-", args[1]))
			if (!(dir = ft_getenv(*env, "OLDPWD")))
				return (ft_perror("env", ": Oldpwd not exists", 1));
		if (isdir(dir))
			change_dir(dir, env);
		else if (!access(dir, F_OK))
			ft_perror(dir, ": Not a directory", 1);
		else
			ft_perror(dir, ": No such file or directory", 1);
	}
	else if ((dir = ft_getenv(*env, "HOME")))
		change_dir(dir, env);
	else
		ft_perror("env", ": Home not exists", 1);
	return (0);
}
