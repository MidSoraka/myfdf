/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_placement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:45:29 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/15 01:06:00 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	coords_for_drawing(int x, int y, t_prm *prm)
{
	prm->xyz[2][X] = prm->coord_copy[prm->xyz[0][Y]][prm->xyz[0][X]][X];
	prm->xyz[2][Y] = prm->coord_copy[prm->xyz[0][Y]][prm->xyz[0][X]][Y];
	prm->xyz[1][X] = prm->coord_copy[prm->xyz[0][Y] + y][prm->xyz[0][X] + x][X];
	prm->xyz[1][Y] = prm->coord_copy[prm->xyz[0][Y] + y][prm->xyz[0][X] + x][Y];
	get_color(x, y, prm);
	get_z_height(x, y, prm);
	draw_line(prm);
}

static void	draw_image(t_prm *prm)
{
	prm->xyz[0][Y] = 0;
	while (prm->coord[prm->xyz[0][Y]])
	{
		prm->xyz[0][X] = 0;
		while (prm->coord[prm->xyz[0][Y]][prm->xyz[0][X]])
		{
			if (prm->xyz[0][X] > 0)
				coords_for_drawing(-1, 0, prm);
			if (prm->xyz[0][Y] > 0)
				coords_for_drawing(0, -1, prm);
			prm->xyz[0][X]++;
		}
		prm->xyz[0][Y]++;
	}
}

static void	copy_numbers(t_prm *prm)
{
	int	x;
	int	y;

	y = 0;
	while (prm->coord[y])
	{
		x = 0;
		while (prm->coord[y][x])
		{
			prm->coord_copy[y][x][0] = prm->coord[y][x][0];
			prm->coord_copy[y][x][1] = prm->coord[y][x][1];
			prm->coord_copy[y][x][2] = prm->coord[y][x][2];
			rotation_matrices(prm->coord_copy[y][x], prm);
			x++;
		}
		y++;
	}
}

void	pixel_placement(t_prm *prm)
{
	int	index;

	index = 0;
	while (index < prm->win_x * prm->win_y)
		prm->z_buffer[index++] = INT_MAX;
	copy_numbers(prm);
	if (prm->isfill == 0)
	{
		prm->color = INT_MAX;
		draw_image(prm);
	}
	else
		fill_image(prm);
}
