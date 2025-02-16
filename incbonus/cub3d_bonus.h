/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:29:23 by iestero-          #+#    #+#             */
/*   Updated: 2025/02/16 12:58:07 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft.h"
# include "get_next_line.h"

# include "quatlib.h"

# include "structs_bonus.h"
# include "constants_bonus.h"
# include "parse_bonus.h"
# include "events_bonus.h"
# include "utils_bonus.h"

# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <error.h>
# include <math.h>

/* RENDER */
void	render(t_cub3d *cub3d);

/* INIT */
void	init(t_cub3d *cub3d);

#endif
