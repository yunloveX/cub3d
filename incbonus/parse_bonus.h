/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:30:53 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/17 08:23:12 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

# include "libft.h"

# include "structs_bonus.h"
# include "utils_bonus.h"

void	parse(t_cub3d *cub3d, char *file);

int		parse_map(int fd, t_map *map);
int		parse_options(char *line, t_cub3d *cub3d);
void	parse_player(t_cub3d *cub3d);

#endif
