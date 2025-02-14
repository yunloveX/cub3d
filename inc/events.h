/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:57:04 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/14 10:00:28 by iestero-         ###   ########.fr       */
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
void	mouse_hook_function(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);
void	scroll_hook_function(double xdelta, double ydelta, void *param);

/* KEY EVENTS */
void	key_hook_function(mlx_key_data_t key_data, void *param);

/* CLOSE EVENTS */
void	close_hook_function(void *param);

#endif