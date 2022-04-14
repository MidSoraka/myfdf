/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:15:25 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/15 01:51:57 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_color(int x, int y, t_prm *prm)
{
	double			height;
	unsigned int	r;
	unsigned int	b;
	int				temp_x;
	int				temp_y;

	temp_x = prm->xyz[0][X];
	temp_y = prm->xyz[0][Y];
	if (temp_y == 0)
		temp_y++;
	if (temp_x == 0)
		temp_x++;
	height = prm->coord[temp_y - 1][temp_x - 1][2];
	if (prm->coord[temp_y + y][temp_x + x][2] > height)
		height = prm->coord[temp_y + y][temp_x + x][2];
	if (prm->coord[temp_y][temp_x][2] > height)
		height = prm->coord[temp_y][temp_x][2];
	prm->min_height = abs(prm->min_height);
	prm->max_height = abs(prm->max_height);
	//printf("min is %d\n max is %d\n\n",  prm->min_height, prm->max_height);
	//printf("height is %f\n", height);
	height = height + prm->min_height;
	height = height / (prm->min_height + prm->max_height);
	prm->color = 0;
	r = (height * 255);
	b = 255 - r;
	prm->color = b + (r << 16);
}

void	get_z_height(int x, int y, t_prm *prm)
{
	int	temp_x;
	int	temp_y;

	temp_x = prm->xyz[0][X];
	temp_y = prm->xyz[0][Y];
	if (temp_y == 0)
		temp_y++;
	if (temp_x == 0)
		temp_x++;
	prm->xyz[0][Z] = prm->coord_copy[temp_y - 1][temp_x - 1][Z];
	if (prm->xyz[0][Z] < prm->coord_copy[temp_y + y][temp_x + x][Z])
	prm->xyz[0][Z] = prm->coord_copy[temp_y + y][temp_x + x][Z];
	if (prm->xyz[0][Z] < prm->coord_copy[temp_y][temp_x][Z])
	prm->xyz[0][Z] = prm->coord_copy[temp_y][temp_x][Z];
}

void	rotation_matrices(int *vector3, t_prm *prm)
{
	int		v3[3];
	int		ptr[3];
	double	alpha;
	double	beta;

	alpha = (prm->alpha * M_PI) / 180;
	beta = (prm->beta * M_PI) / 180;
	v3[0] = vector3[0] * prm->scale_xyz[0];
	v3[1] = vector3[1] * prm->scale_xyz[1];
	v3[2] = vector3[2] * prm->scale_xyz[2];
	ptr[0] = (v3[0] * 1) + (v3[1] * 0) + (v3[2] * 0);
	ptr[1] = (v3[0] * 0) + (v3[1] * cos(alpha)) + (v3[2] * sin(alpha));
	ptr[2] = (v3[0] * 0) + (v3[1] * -sin(alpha)) + (v3[2] * cos(alpha));
	v3[0] = ptr[0];
	v3[1] = ptr[1];
	v3[2] = ptr[2];
	vector3[0] = (v3[0] * cos(beta)) + (v3[1] * 0) + (v3[2] * -sin(beta));
	vector3[2] = (v3[0] * 0) + (v3[1] * 1) + (v3[2] * 0);
	vector3[1] = (v3[0] * sin(beta)) + (v3[1] * 0) + (v3[2] * cos(beta));
}
