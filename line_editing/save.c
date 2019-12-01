/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:47:01 by llachgar          #+#    #+#             */
/*   Updated: 2019/12/01 07:11:05 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

t_cmd	*keep_l(t_cmd *l, int cmd)
{
	static t_cmd *tmp;

	if (cmd)
		return (tmp);
	tmp = l;
	return (l);
}

t_hist	*save_hist(t_hist *hist)
{
	static t_hist *tmp;

	if (hist == NULL)
		return (tmp);
	tmp = hist;
	return (hist);
}

void	excute_key(t_key keys[18], t_cmd *l)
{
	int i;

	i = -1;
	while (++i < 18)
		if (l->key == keys[i].key)
			keys[i].f(l);
}
