/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:10:44 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/13 09:50:05 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "get_next_line.h"

# include "quatlib.h"

# include "structs.h"
# include "constants.h"
# include "utils.h"

# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <error.h>
# include <math.h>
# include <time.h>

/* EVENT UTILS */
void		rotate_horizontal(t_cub3d *cub3d, double xpos);
void		move(t_cub3d *cub3d, double step);

/* DRAW UTILS */
void		drawline(t_cub3d *cub3d, double tx_h, double dist,
				int side_height[2]);

/* COLOR UTILS */
uint32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t	color_from_mem(uint8_t *pixel);
int			transp(uint32_t color);
void		transparent_pixel(uint8_t *pixel, uint32_t color);

/* STRING UTILS */
char		**ft_dstrdup(char **dstr, int size);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void		double_free(void **ptr);
int			ft_strcmp(char *s1, char *s2);

/* CAM UTILS */
void		locate_pos(t_cub3d *cub3d);
void		locate_cam(t_cub3d *cub3d);
void		player_equal(t_player *player_to, t_player *player_from);

/* IMAGES UTILS */
void		blend_images(mlx_image_t *dst, mlx_texture_t *src, int scale);
void		sprite(t_cub3d *cub3d);

/* ERROR UTILS */
void		cub3d_error(char *message, int error, t_cub3d *cub3d);

/* MAP UTILS*/
char		*skip_empty_lines(int fd);
int			check_line(char *line);
void		check_cell(char **grid, int y, int x, int height);
void		find_zero(char **grid, int *y, int *x, int rows);
int			check_map(char **grid, int rows);

/* RAYCAST UTILS*/
char		map(t_cub3d *cub3d, int x, int y);
int			raycast(t_cub3d *cub3d, int h, double *tx_h, double *dist);

/* WALL UTILS */
int			meet_wall(t_cub3d *cub3d, t_quaternion progress, t_quaternion ray,
				double *tx_h);

#endif