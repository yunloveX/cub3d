/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_ops3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:24:55 by nulsuga           #+#    #+#             */
/*   Updated: 2025/02/14 10:44:12 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quatlib.h"

t_quaternion	q_gaps(t_quaternion point, t_quaternion dir)
{
	t_quaternion	ret;

	ret.r = 0.0;
	ret.i = ceil(point.i) - point.i;
	if (dir.i < 0)
		ret.i = ret.i - 1;
	else if (ret.i == 0)
		ret.i = 1;
	ret.j = ceil(point.j) - point.j;
	if (dir.j < 0)
		ret.j = ret.j - 1;
	else if (ret.j == 0)
		ret.j = 1;
	ret.k = 0;
	return (ret);
}
