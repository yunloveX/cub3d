/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:23 by iestero-          #+#    #+#             */
/*   Updated: 2024/07/02 18:48:40 by yunlovex         ###   ########.fr       */
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

# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <error.h>
# include <math.h>




//uint32_t	raycast(t_cub3d *cub3d, int h, int v);

void	render(t_cub3d *cub3d);

void    loop_hook_function(void *param);

void	mouse_hook_function(mouse_key_t button, action_t action, modifier_key_t mods, void* param);

void	scroll_hook_function(double xdelta, double ydelta, void *param);

void	key_hook_function(mlx_key_data_t key_data, void *param);

//void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	locate_pos(t_cub3d *cub3d);

void	locate_cam(t_cub3d *cub3d);

void	init(t_cub3d *cub3d);

char	**ft_dstrdup(char **dstr, int size);

uint32_t	color_from_mem(uint8_t *pixel);

uint32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

void	cub3d_error(char *message, int error);

void	double_free(char **str);

#endif
