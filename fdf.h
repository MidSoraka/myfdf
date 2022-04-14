/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:58:37 by vlaine            #+#    #+#             */
/*   Updated: 2022/04/14 02:38:50 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define BUTTON_ESC 53
# define INT_MAX 2147483647
# define X 0
# define Y 1
# define Z 2
# define KEY_X 7
# define KEY_C 8
# define KEY_Y 16
# define KEY_U 32
# define KEY_F 3
# define KEY_R 15
# define KEY_ESC 53
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_UP 126
# define KEY_DOWN 125
# define TRUE 1
# define FALSE 0
# define BOOL int
# define UINT unsigned int *
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
#include <stdio.h> // remove

typedef struct s_prm
{
	struct s_mlx		*mlx;
	struct s_brez_line	*brez_var;
	double				alpha;
	double				beta;
	int					loc_xyz[3];
	int					xyz[3][3];
	int					min_height;
	int					max_height;
	int					win_x;
	int					win_y;
	int					scale_xyz[3];
	int					***coord;
	int					***coord_copy;
	int					*z_buffer;
	int					bpp;
	int					size_line;
	int					erdian;
	int					isfill;
	unsigned int		color;
	int					mid_x[2];
	int					mid_y[2];
}						t_prm;

typedef struct s_brez_line
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				e2;
	int				error;
}					t_brez;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image_ptr;
	char		*image_add;
}				t_mlx;

typedef struct s_fdf
{
	char			*line;
	int				x;
	int				y;
	struct s_fdf	*next;
}					t_fdf;

void	rotation_matrices(int *vector3, t_prm *prm);
void	sort_coordinates(t_prm *prm);
void	pixel_placement(t_prm *prm);
void	read_file(t_prm *prm, int fd);
void	free_all(t_prm *prm, t_fdf *head, char *error_msg, BOOL error);
void	free_prm(t_prm *prm);
void	free_fdf(t_fdf *head);
int		keycode_hook(int key, void *prm);
int		open_fd(char *file, int argc, t_prm *prm);
int		mlx_window_loop(void *prm);
void	open_window(t_prm *prm);
void	fill_image(t_prm *prm);
void	draw_line(t_prm *prm);
void	malloc_coordinates(t_prm *prm, t_fdf *head);
void	get_color(int x, int y, t_prm *prm);
void	get_z_height(int x, int y, t_prm *prm);
void	triangle_coords(int x, int y, int *triangle, t_prm *prm);
void	brez_swap(int *x, int *y, t_brez *brez_var);
int		brez_pixel(int *x, int *y, t_brez *brez_var);
void	error_check(t_prm *prm, t_fdf *head);

#endif
