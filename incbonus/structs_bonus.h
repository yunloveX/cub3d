/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:59:26 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/16 12:58:33 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# include "MLX42/MLX42.h"
# include "quatlib.h"

# include "linked_list.h"

typedef struct s_map
{
	char	**grid;
	int		**door_states;
	int		width;
	int		height;
}	t_map;

typedef struct s_colors
{
	uint32_t	floor_color;
	uint32_t	ceiling_color;
}	t_colors;

typedef struct s_player
{
	t_quaternion	pos;
	t_quaternion	right;
	t_quaternion	down;
	t_quaternion	cam;
}	t_player;

typedef struct s_cub3d
{
	void			*win;
	mlx_t			*mlx;
	t_map			map;
	t_list			*hand_frame;
	t_list			**hand_texture;
	int32_t			old_x;
	int32_t			old_y;
	t_colors		colors;
	t_player		player;
	t_player		player_old;
	mlx_image_t		*img;
	mlx_texture_t	*img_map;
	mlx_texture_t	*textures[5];
	int				mouse_down;
	int				hand_playing;
	int				slow_count;
	int				frames_shown;
	int				temp_door_x;
	int				temp_door_y;
	double			jumps[3];
}	t_cub3d;

#endif