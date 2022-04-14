/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_coordinates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:45:20 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/15 01:51:44 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	str_to_int(char *str, t_prm *prm, t_fdf *head)
{
	int		index;

	index = 0;
	while (ft_isdigit(str[index]) == 1 || (index == 0 && str[index] == '-'))
		index++;
	if ((index > 3 && str[0] != '-') || (str[0] == '-' && index > 4))
	{
		free_fdf(head);
		ft_putendl("error");
		exit(0);
	}
	index = ft_atoi(str);
//	if (str[0] == '-')
//		printf("index is %d\n\n\n\n\n", index); // remove
	return (index);
}

static void	set_coords(t_prm *prm, t_fdf *head, int z)
{
	int	x;
	int	y;

	x = prm->xyz[0][X];
	y = prm->xyz[0][Y];
	prm->coord[y][x] = (int *)malloc(sizeof(int) * 3);
	prm->coord_copy[y][x] = (int *)malloc(sizeof(int) * 3);
	if (prm->coord[y][x] == NULL || prm->coord_copy[y][x] == NULL)
		free_all(prm, head, "error", TRUE);
	prm->coord[y][x][0] = x;
	prm->coord[y][x][1] = y;
	prm->coord[y][x][2] = z;
	if (z > prm->max_height)
		prm->max_height = z;
	if (z < prm->min_height)
		prm->min_height = z;
}

static void	gnl_line_len(t_prm *prm, t_fdf *head, t_fdf *elem)
{
	int	index;
	int	x;
	int	y;

	x = prm->xyz[0][X];
	y = prm->xyz[0][Y];
	index = 0;
	x = 0;
	while (elem->line[index])
	{
		if (index > 0)
			if ((elem->line[index - 1] != ' ' && elem->line[index] == ' ') || \
			elem->line[index + 1] == '\0')
				x++;
		index++;
	}
	prm->coord[y] = (int **)malloc((x + 1) * sizeof(int *));
	if (prm->coord[y] == NULL)
		free_all(prm, head, "error", TRUE);
	prm->coord[y][x] = NULL;
	prm->coord_copy[y] = (int **)malloc((x + 1) * sizeof(int *));
	if (prm->coord_copy[y] == NULL)
		free_all(prm, head, "error", TRUE);
	prm->coord_copy[y][x] = NULL;
}

static void	gnl_line_to_coords(t_prm *prm, t_fdf *head, t_fdf *elem)
{
	int	index;

	index = 0;
	prm->xyz[0][X] = 0;
	while (elem->line[index])
	{
		if (ft_isdigit(elem->line[index]) != 1 && elem->line[index] != ' ' && \
		elem->line[index] != '-')
			free_all(prm, head, "error", TRUE);
		if (elem->line[index] != ' ' && (index == 0 || \
		elem->line[index - 1] == ' '))
		{
			set_coords(prm, head, str_to_int(&elem->line[index], prm, head));
			prm->xyz[0][X]++;
		}
		index++;
	}
	prm->xyz[0][Y]++;
}

void	malloc_coordinates(t_prm *prm, t_fdf *head)
{
	t_fdf	*elem;
	int		index;

	elem = head;
	prm->xyz[0][Y] = 0;
	while (elem)
	{
		gnl_line_len(prm, head, elem);
		gnl_line_to_coords(prm, head, elem);
		elem = elem->next;
	}
	free_fdf(head);
}
