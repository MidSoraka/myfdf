/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 01:29:29 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/14 21:29:59 by vlaine           ###   ########.fr       */
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
	else
		return (x);
}

static void	elem_parser(t_prm *prm, t_fdf *head)
{
	t_fdf	*elem;
	int		last_index;
	int		index;
	char	ch;

	elem = head;
	index = 0;
	last_index = -1;
	while (elem)
	{
		index = line_parser(elem->line);
		if (last_index == -1)
			last_index = index;
		if (last_index != index || index < 0)
			free_all(NULL, head, "error", TRUE);
		elem = elem->next;
	}
	if (!head->next || index < 2)
		free_all(NULL, head, "error", TRUE);
}

void	error_check(t_prm *prm, t_fdf *head)
{
	t_fdf	*elem;

	elem = head;
	elem_parser(prm, head);
}
