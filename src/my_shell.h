/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:31:10 by hastid            #+#    #+#             */
/*   Updated: 2019/11/21 05:58:02 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SHELL_H
# define MY_SHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
#include <fcntl.h>

typedef struct	s_tok
{
	int				id;
	char			*value;
	struct s_tok	*next;
}				t_tok;

typedef struct	s_line
{
	int		rd;
	char	**args;
}				t_line;

typedef struct	s_fd
{
	int				fir;
	int				sec;
	struct	s_fd	*next;
}				t_fd;

typedef struct	s_cmdl
{
	int		rd;
	t_fd	*lrd;
	char	**args;
}				t_cmdl;

int				split_lines(char *line, char **env);
int				analy_toks(t_tok *toks);
int				check_error(t_tok *toks);
t_cmdl			*save_to_excute(t_tok *toks);

int				check_space(char c);
int				check_spechar(char c);
int				check_token(char *token);
int				check_number(char *token);

void			free_tab(char **tab);
void			free_tokens(t_tok *lst);
void			free_cmdline(t_cmdl *cmdl);
int				save_tokens(t_tok **tok, char *token, int id);

int				add_args(t_cmdl *cmdl, t_tok *toks);

int				execute_cmdl(t_cmdl *cmdl, char **env);

int				ft_perror(char *s, char *str);

#endif
