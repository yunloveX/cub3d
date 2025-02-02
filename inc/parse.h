/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:30:53 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/03 13:11:29 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"

void	parse(t_cub3d *cub3d, char *file);

int		parse_map(int fd, t_map *map);
int		parse_options(char *line, t_cub3d *cub3d);
void	parse_player(t_cub3d *cub3d);

#endif

