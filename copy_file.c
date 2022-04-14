/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:34:00 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/14 21:09:32 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fdf	*new_list(t_fdf *head)
{
	t_fdf	*new;

	new = malloc(sizeof(t_fdf));
	if (new == NULL)
	{
		free_fdf(head);
		exit (0);
	}
	new->next = NULL;
	return (new);
}

static void	gnl_file(t_prm *prm, t_fdf *head, int fd)
{
	int		gnl;
	char	*line;
	t_fdf	*elem;

	gnl = 1;
	prm->xyz[0][X] = 0;
	elem = head;
	prm->erdian = 1;
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		if (gnl > 0)
		{
			if (prm->erdian != 1)
				elem->next = new_list(head);
			if (prm->erdian != 1)
				elem = elem->next;
			elem->line = ft_strnew(ft_strlen(line));
			ft_strcpy(elem->line, line);
			ft_bzero(line, ft_strlen(line));
			free(line);
			prm->erdian = 0;
			prm->xyz[0][X]++;
		}
	}
}

void	read_file(t_prm *prm, int fd)
{
	t_fdf	*head;
	t_fdf	*elem;
	char	*line;
	int		gnl;

	head = new_list(NULL);
	elem = head;
	gnl = 1;
	prm->erdian = 1;
	gnl_file(prm, head, fd);
	error_check(prm, head);
	prm->coord = (int ***)malloc((prm->xyz[0][X] + 1) * sizeof(int **));
	prm->coord_copy = (int ***)malloc((prm->xyz[0][X] + 1) * sizeof(int **));
	if (prm->coord == NULL || prm->coord_copy == NULL)
		exit(0);
	prm->coord[prm->xyz[0][X]] = NULL;
	prm->coord_copy[prm->xyz[0][X]] = NULL;
	malloc_coordinates(prm, head);
}
