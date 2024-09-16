/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2024/07/02 18:48:33 by yunlovex         ###   ########.fr       */
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

char	**ft_dstrdup(char **dstr, int size)
{
	char	**copy;
	int		i;

	copy = (char **) malloc(size * sizeof(char *));
	i = -1;
	while (++i < size)
		copy[i] = ft_strdup(dstr[i]);
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
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memset(new_ptr, 0, new_size);
	if (new_size < old_size)
		copy_size = new_size;
	else
		copy_size = old_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
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
void	double_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	free(str);
}
