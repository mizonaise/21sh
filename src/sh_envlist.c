/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_envlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 06:31:08 by hastid            #+#    #+#             */
/*   Updated: 2019/11/24 10:56:34 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

t_env	*elem_env(char *name, char *value)
{
	t_env	*elem;

	if (!(elem = (t_env *)malloc(sizeof(t_env))))
		return (0);
	if (!(elem->name = ft_strdup(name)))
		return (0);
	if (value)
		if (!(elem->value = ft_strdup(value)))
			return (0);
	if (!value)
		elem->value = ft_strdup("\0");
	elem->next = 0;
	return (elem);
}

int		add_to_env(t_env **env, char *name, char *value)
{
	t_env	*tmp;

	if (*env)
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = elem_env(name, value)))
			return (1);
	}
	else if (!(*env = elem_env(name, value)))
		return (1);
	return (0);
}

t_env	*creat_env(char **env)
{
	int		i;
	int		co;
	char	*tmp;
	char	*name;
	t_env	*my_env;

	i = 0;
	my_env = 0;
	while (env && env[i])
	{
		tmp = env[i];
		co = 0;
		while (tmp[co] != '=')
			co++;
		name = ft_strsub(tmp, 0, co);
		add_to_env(&my_env, name, tmp + co + 1);
		i++;
	}
	return (my_env);
}

int		add_elem(t_env **env, char *name, char *value)
{
	t_env	*tmp;

	tmp = *env;
	if (name)
	{
		while (tmp && ft_strcmp(name, tmp->name))
			tmp = tmp->next;
		if (tmp)
		{
			ft_memdel((void **)&tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = ft_strdup("\0");
		}
		else
			add_to_env(env, name, value);
	}
	else
		ft_putenv(tmp);
	return (0);
}

int		del_head(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	*env = (*env)->next;
	ft_memdel((void **)&tmp->name);
	ft_memdel((void **)&tmp->value);
	ft_memdel((void **)&tmp);
	return (0);
}

int		del_elem(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	if (*env && !ft_strcmp(name, (*env)->name))
		return (del_head(env));
	tmp = *env;
	while (tmp && ft_strcmp(name, tmp->name))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		prev->next = tmp->next;
		ft_memdel((void **)&tmp->name);
		ft_memdel((void **)&tmp->value);
		ft_memdel((void **)&tmp);
	}
	return (0);
}

void	ft_putenv(t_env *env)
{
	while (env)
	{
		ft_putstr(env->name);
		ft_putchar('=');
		ft_putendl(env->value);
		env = env->next;
	}
}
