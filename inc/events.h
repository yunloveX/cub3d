/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:57:04 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/16 17:08:00 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "libft.h"
# include "get_next_line.h"

# include "quatlib.h"

# include "structs.h"
# include "constants.h"
# include "parse.h"
# include "utils.h"
# include "cub3d.h"

# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <error.h>
# include <math.h>

/* LOOP EVENTS */
void	loop_hook_function(void *param);

/* MOUSE EVENTS */

/* KEY EVENTS */
void	key_hook_function(mlx_key_data_t key_data, void *param);

/* CLOSE EVENTS */
void	close_hook_function(void *param);

#endif