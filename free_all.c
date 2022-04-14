/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:42:41 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/15 01:49:42 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_prm(t_prm *prm)
{
	int	x;
	int	y;

	y = 0;
	while (prm->coord[y])
	{
		x = 0;
		while (prm->coord[y][x])
		{
			free(prm->coord_copy[y][x]);
			free(prm->coord[y][x]);
			x++;
		}
		free(prm->coord_copy[y]);
		free(prm->coord[y]);
		y++;
	}
	free(prm->coord);
	free(prm->coord_copy);
	free(prm->z_buffer);
	mlx_destroy_image(prm->mlx->mlx_ptr, prm->mlx->image_ptr);
}

void	free_fdf(t_fdf *head)
{
	t_fdf	*hold;

	while (head)
	{
		hold = head->next;
		free(head->line);
		free(head);
		head = hold;
	}
	free(head);
}

void	free_all(t_prm *prm, t_fdf *head, char *error_msg, BOOL error)
{
	if (prm)
		free_prm(prm);
	if (head)
		free_fdf(head);
	if (error == TRUE && error_msg)
		ft_putendl(error_msg);
	exit(0);
}
