/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 01:21:51 by hastid            #+#    #+#             */
/*   Updated: 2019/11/24 12:21:28 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		check_quotes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == c)
			return (1);
	return (0);
}

int		check_redirect(char *str)
{
	int		i;
	char	*rd;

	i = 0;
	while (check_spechar(str[i]))
		i++;
	if (!str[i])
	{
		ft_putendl("21sh: syntax error near unexpected token");
		return (1);
	}
	rd = ft_strsub(str, 0, i);
	if (!ft_strcmp(rd, ">") || !ft_strcmp(rd, ">>") || !ft_strcmp(rd, ">&"))
		return (0);
	if (!ft_strcmp(rd, "<") || !ft_strcmp(rd, "<<") || !ft_strcmp(rd, "<&"))
		return (0);
	if (!ft_strcmp(rd, "&>") || !ft_strcmp(rd, "&<"))
		return (0);
	ft_memdel((void **)&rd);
	ft_putendl("21sh: syntax error near unexpected token");
	return (1);
}

int		check_line(char *str)
{
	int	i;
	int	be;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			be = i++;
			if (!check_quotes(str + i, str[be]))
				return (1);
			while (str[i] && str[i] != str[be])
				i++;
		}
		if (str[i] == '|' && !str[i + 1])
			return (1);
		if (check_spechar(str[i]))
			if (check_redirect(str + i))
				return (-1);
		i++;
	}
	return (0);
}

char	*prompt_21sh(void)
{
	int		ret;
	char	*tmp;
	char	*temp;
	char	*line;

	line = readline("21sh >$ ");
	ret = check_line(line);
	while (ret > 0)
	{
		tmp = line;
		temp = readline("> ");
		line = ft_strjoin(line, temp);
		ft_memdel((void **)&tmp);
		ft_memdel((void **)&temp);
		ret = check_line(line);
	}
	add_history(line);
	if (ret == -1)
	{
		ft_memdel((void **)&line);
		return (0);
	}
	return (line);
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*my_env;

	my_env = creat_env(env);
	while (1337)
	{
		if ((line = prompt_21sh()))
		{
			if (!ft_strcmp(line, "exit"))
			{
				ft_memdel((void **)&line);
				break ;
			}
			split_lines(line, &my_env);
			ft_memdel((void **)&line);
		}
	}
	return (0);
}
