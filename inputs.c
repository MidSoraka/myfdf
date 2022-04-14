/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:40:32 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/14 02:38:36 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	scaling_keys(int key, t_prm *prm)
{
	int	scale_x;
	int	scale_y;

	scale_x = prm->xyz[0][X] * prm->scale_xyz[0];
	scale_y = prm->xyz[0][Y] * prm->scale_xyz[1];
	if (key == KEY_PLUS)
	{
		if (scale_x < prm->win_x && scale_y < prm->win_y)
		{
			prm->scale_xyz[X] = prm->scale_xyz[X] + 2;
			prm->scale_xyz[Y] = prm->scale_xyz[Y] + 2;
			prm->scale_xyz[Z] = prm->scale_xyz[Z] + 1;
		}
	}
	if (key == KEY_MINUS)
	{
		if (prm->scale_xyz[X] > 2)
		{
			prm->scale_xyz[X] = prm->scale_xyz[X] - 2;
			prm->scale_xyz[Y] = prm->scale_xyz[Y] - 2;
			prm->scale_xyz[Z] = prm->scale_xyz[Z] - 1;
		}
	}
}

static void	movement_keys(int key, t_prm *prm)
{
	if (key == KEY_DOWN)
		prm->alpha += 5;
	if (key == KEY_UP)
		prm->alpha -= 5;
	if (key == KEY_LEFT)
		prm->beta += 5;
	if (key == KEY_RIGHT)
		prm->beta -= 5;
	if (key == KEY_X)
		prm->loc_xyz[X] += 50;
	if (key == KEY_C)
		prm->loc_xyz[X] -= 50;
	if (key == KEY_Y)
		prm->loc_xyz[Y] += 50;
	if (key == KEY_U)
		prm->loc_xyz[Y] -= 50;
}

static void	function_keys(int key, t_prm *prm)
{
	if (key == KEY_R)
	{
		prm->loc_xyz[X] = 0;
		prm->loc_xyz[Y] = 0;
		prm->alpha = 0;
		prm->beta = 0;
		prm->scale_xyz[X] = 4;
		prm->scale_xyz[Y] = 4;
		prm->scale_xyz[Z] = 2;
	}
	if (key == KEY_F)
	{
		if (prm->isfill == 0)
			prm->isfill = 1;
		else
			prm->isfill = 0;
	}
	if (key == KEY_ESC)
		free_all(prm, NULL, "exit", FALSE);
}

int	mlx_window_loop(void *prm)
{
	t_prm	*local;
	t_mlx	*mlx;

	local = ((t_prm *)prm);
	mlx = local->mlx;
	ft_bzero(mlx->image_add, local->win_x * local->win_y * sizeof(int));
	pixel_placement(local);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image_ptr, 0, 0);
	mlx_do_sync(mlx->mlx_ptr);
	return (0);
}

int	keycode_hook(int key, void *prm)
{
	t_prm	*local;

	local = ((t_prm *)prm);
	function_keys(key, local);
	movement_keys(key, local);
	scaling_keys(key, local);
	return (0);
}
