/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:23 by iestero-          #+#    #+#             */
/*   Updated: 2025/02/03 12:05:09 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"

# include "quatlib.h"

# include "structs.h"
# include "constants.h"
# include "parse.h"
# include "events.h"

# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <error.h>
# include <math.h>

void	render(t_cub3d *cub3d);

void	locate_pos(t_cub3d *cub3d);

void	locate_cam(t_cub3d *cub3d);

void	init(t_cub3d *cub3d);

void	player_equal(t_player *player_to, t_player *player_from);

char	**ft_dstrdup(char **dstr, int size);

void    transparent_pixel(uint8_t *pixel, uint32_t color);

void blend_images(mlx_image_t* base, mlx_texture_t* overlay, int x_offset, int y_offset);

uint32_t	color_from_mem(uint8_t *pixel);

uint32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

void	cub3d_error(char *message, int error);

void	double_free(char **str);

#endif
