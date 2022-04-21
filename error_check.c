/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 01:29:29 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/21 14:28:03 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	line_parser(char *str)
{
	char	ch;
	int		index;
	int		x;

	index = 0;
	x = 0;
	while (str[index] && index >= 0)
	{
		ch = str[index];
		if (!(ft_isdigit(ch) || ch == ' ' || ch == '-'))
			index = -2;
		if ((str[0] == ' ' || !ft_isdigit(str[0])) && str[0] != '-')
			index = -2;
		if (ch != ' ' && (index == 0 || str[index - 1] == ' '))
			x++;
		index++;
	}
	if (index <= 1)
		return (-1);
	if (index > 0)
		index--;
	if (!(ft_isdigit(str[index])))
		return (-1);
	return (x);
}

void	error_check(t_prm *prm)
{
	t_fdf	*elem;
	int		last_index;
	int		index;

	elem = prm->head;
	index = 0;
	last_index = -1;
	while (elem)
	{
		index = line_parser(elem->line);
		if (last_index == -1)
			last_index = index;
		if (last_index != index || index < 0)
			exit_window(prm, "error", TRUE);
		elem = elem->next;
	}
	if (!prm->head->next || index < 2)
		exit_window(prm, "error", TRUE);
}
