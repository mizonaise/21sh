/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 00:50:25 by hastid            #+#    #+#             */
/*   Updated: 2019/12/15 05:19:07 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"
#include <sys/wait.h>

static t_pipe	*add_pipe(t_cmdl *cmdl, t_tok *tok)
{
	t_pipe	*pi;

	if (!(pi = (t_pipe *)malloc(sizeof(t_pipe))))
		return (0);
	pi->tok = tok;
	pi->cmdl = cmdl;
	pi->next = 0;
	return (pi);
}

static t_tok	*pipe_toks(char *line)
{
	t_tok	*tmp;
	t_tok	*toks;

	if ((toks = split_tokens(line)))
	{
		tmp = toks;
		if (analy_toks(tmp) || check_error(tmp))
		{
			ft_memdel((void **)&line);
			return (0);
		}
	}
	ft_memdel((void **)&line);
	return (toks);
}

static int		add_pipes(t_pipe **pipes, char *line)
{
	t_tok	*tmp;
	t_cmdl	*cmdl;
	t_pipe	*temp;

	if (!(tmp = pipe_toks(line)))
		return (0);
	if ((cmdl = save_to_excute(tmp)))
	{
		if (!(*pipes))
		{
			if (!(*pipes = add_pipe(cmdl, tmp)))
				return (1);
		}
		else
		{
			temp = *pipes;
			while (temp->next)
				temp = temp->next;
			if (!(temp->next = add_pipe(cmdl, tmp)))
				return (1);
		}
		return (0);
	}
	return (1);
}

static int		execute_pipe(t_pipe *pipes, t_env **env)
{
	int		inp;
	int		len;
	int		pi[2];

	inp = 0;
	len = 0;
	while (pipes)
	{
		if ((pipes->cmdl->args) && ft_strcmp(pipes->cmdl->args[0], "exit"))
		{
			if (pipes->next)
				if (pipe(pi) == -1)
					return (ft_perror(0, "pipe failed", 1));
			if (execute_p(inp, pi, env, pipes))
				break ;
			len++;
			inp = pi[0];
		}
		pipes = pipes->next;
	}
	close(pi[0]);
	while (len--)
		wait(0);
	return (0);
}

int				split_pipe(char *line, t_env **env)
{
	char	*tmp;
	t_pipe	*pipes;

	pipes = 0;
	while (*line)
	{
		while (*line && check_space(*line))
			line++;
		if (*line)
		{
			line = sub_line(&tmp, line, '|');
			if (tmp)
				if (add_pipes(&pipes, tmp))
				{
					free_pipes(pipes);
					return (1);
				}
		}
	}
	execute_pipe(pipes, env);
	free_pipes(pipes);
	return (0);
}
