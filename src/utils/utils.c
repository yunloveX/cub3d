/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2024/06/30 16:06:08 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


int	create_trgb(int t, int r, int g, int b)
{
	if (t > 255 || r > 255 || g > 255 || b > 255)
		return (-1);
	if (t < 0 || r < 0 || g < 0 || b < 0)
		return (-1);
	return (t << 24 | r << 16 | g << 8 | b);
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
