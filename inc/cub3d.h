/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:23 by iestero-          #+#    #+#             */
/*   Updated: 2024/06/30 16:34:20 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"

# include "mlx.h"
# include "mlx_int.h"

# include "structs.h"
# include "constants.h"
# include "parse.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <error.h>
# include <math.h>



void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	init(t_cub3d *cub3d);

char	**ft_dstrdup(char **dstr, int size);

int		create_trgb(int t, int r, int g, int b);

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif