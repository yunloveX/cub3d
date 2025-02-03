/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:10:44 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/03 12:22:15 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"
# include "constants.h"


/* EVENT UTILS */
void	rotate_horizontal(t_cub3d *cub3d, double xpos);
void	move(t_cub3d *cub3d, double step);

/* COLOR UTILS */
uint32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t	color_from_mem(uint8_t *pixel);
int	        transp(uint32_t color)
void        transparent_pixel(uint8_t *pixel, uint32_t color)

/* STRING UTILS */
char	**ft_dstrdup(char **dstr, int size);
void    *ft_realloc(void *ptr, size_t old_size, size_t new_size);
void    double_free(char **str);

/* CAM UTILS */
void	locate_pos(t_cub3d *cub3d);
void	locate_cam(t_cub3d *cub3d);

/* IMAGES UTILS */
void blend_images(mlx_image_t* base, mlx_texture_t* overlay, int x_offset, int y_offset)

/* ERROR UTILS */
void	cub3d_error(char *message, int error);

#endif