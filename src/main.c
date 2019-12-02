/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 23:07:15 by hastid            #+#    #+#             */
/*   Updated: 2019/12/02 01:30:36 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

void			kill_seg(int seg)
{
	t_cmd	*l;
	char	buf[2];

	(void)seg;
	l = NULL;
	l = keep_l(l, 1);
	if (l != NULL)
	{
		l->res = 0;
		l->ctl_c = 1;
		buf[0] = -62;
		buf[1] = 0;
		ioctl(0, TIOCSTI, buf);
	}
	else
		ft_putchar('\n');
}

int				main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*my_env;

	(void)ac;
	(void)av;
	signal(SIGINT, kill_seg);
	signal(SIGWINCH, win_ch);
	my_env = creat_env(env);
	init_history();
	while (1337)
	{
		if (!(line = aff_prompt("21sh >$ ")))
			break ;
		if (line && *line)
			if (split_lines(line, &my_env) == -1)
				break ;
		if (line)
			ft_memdel((void **)&line);
	}
	free_history();
	if (line)
		ft_memdel((void **)&line);
	free_environ(my_env);
	return (0);
}
