/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringUtils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/12 10:52:54 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**ft_dstrdup(char **dstr, int size)
{
	char	**copy;
	int		i;

	copy = (char **) malloc((size + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
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
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	new_ptr = NULL;
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr && old_size > 0)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
	}
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

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}
