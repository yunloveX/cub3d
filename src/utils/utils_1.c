/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: israel <israel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2025/01/04 17:51:23 by israel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/* YA NO HACE FALTA, LA MLX FUNCIONA BIEN
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}*/

/**
 * @brief Creates a 32-bit rgba color from its constituents.
 *
 * @details This function creates a single unsigned 32-bit color value created from
 * its four constituents, red (most significant byte), green, blue and alpha
 * (less significant byte). Params are unsigned 8-bit integers.
 *
 * @param r The red component.
 * @param g The green component.
 * @param b The blue component.
 * @param a The alpha component (complementary of transparency).
 * @return unsigned 32-bit value.
 */

uint32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	color_from_mem(uint8_t *pixel)
{
	uint32_t	color;

	color = 0;
	color |= ((uint32_t)*pixel++) << 24;
	color |= ((uint32_t)*pixel++) << 16;
	color |= ((uint32_t)*pixel++) << 8;
	color |= (uint32_t)*pixel;
	return (color);
}

char	**ft_dstrdup(char **dstr, int size)
{
	char	**copy;
	int		i;

	copy = (char **) malloc((size + 1) * sizeof(char *));
	if (!copy)
        return NULL;
		
	i = -1;
	while (++i < size)
	{
		if (dstr[i])
            copy[i] = ft_strdup(dstr[i]);
        else
            copy[i] = NULL;
        if (!copy[i] && dstr[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
	}
	copy[size] = NULL;
	return (copy);
}

/**
 * @brief Reallocates memory block.
 *
 * @details This function changes the size of the memory block pointed to by 
 * `ptr` to `new_size` bytes. The contents will be unchanged to the minimum 
 * of the old and new sizes; newly allocated memory will be uninitialized. 
 * If `ptr` is NULL, then the call is equivalent to `malloc(new_size)`, for 
 * all values of `new_size`. If `new_size` is equal to zero, and `ptr` is not 
 * NULL, then the call is equivalent to `free(ptr)`. Unless `ptr` is NULL, 
 * it must have been returned by an earlier call to `malloc()`, `calloc()` or 
 * `realloc()`. If the area pointed to was moved, a `free(ptr)` is done.
 *
 * @param ptr Pointer to the memory area to be reallocated.
 * @param old_size Size of the old memory block.
 * @param new_size New size for the memory block.
 * @return Pointer to the newly allocated memory, or NULL if the allocation 
 * failed.
 */
void *ft_realloc(void *ptr, size_t old_size, size_t new_size) {
    void *new_ptr = NULL;

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;
    if (ptr && old_size > 0) {
        size_t copy_size = old_size < new_size ? old_size : new_size;
        ft_memcpy(new_ptr, ptr, copy_size);
    }
    free(ptr);
    return new_ptr;
}

/**
 * @brief 
 * Frees a double pointer.
 *
 * @details
 * Frees each string in the array, then frees the array itself.
 *
 * @param str The double pointer to free.
 */
void double_free(char **str)
{
    int i;

    if (!str)
        return;
    i = 0;
    while (str[i])
    {
        free(str[i]);
		str[i] = NULL;
        i++;
    }
    free(str);
}

void	locate_pos(t_cub3d *cub3d)
{
	cub3d->player.pos = q_mul(cub3d->player.right, cub3d->player.down);
	cub3d->player.pos = q_add(cub3d->player.cam,
		q_scale(cub3d->player.pos, CUBE_EDGE * CAM_DIST));
}

void	locate_cam(t_cub3d *cub3d)
{
	cub3d->player.cam = q_mul(cub3d->player.right, cub3d->player.down);
	cub3d->player.cam = q_add(cub3d->player.pos,
		q_scale(cub3d->player.cam, -CUBE_EDGE * CAM_DIST));
}

void	player_equal(t_player *player_to, t_player *player_from)
{
	player_to->pos = player_from->pos;
	player_to->right = player_from->right;
	player_to->down = player_from->down;
	player_to->cam = player_from->cam;
}