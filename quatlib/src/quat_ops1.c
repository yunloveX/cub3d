/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quatmath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:48:14 by fsusanna          #+#    #+#             */
/*   Updated: 2023/02/20 19:20:13 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quatlib.h"

t_quaternion	q_add(t_quaternion q1, t_quaternion q2)
{
	q1.r += q2.r;
	q1.i += q2.i;
	q1.j += q2.j;
	q1.k += q2.k;
	return (q1);
}
t_quaternion	q_sub(t_quaternion q1, t_quaternion q2)
{
	q1.r -= q2.r;
	q1.i -= q2.i;
	q1.j -= q2.j;
	q1.k -= q2.k;
	return (q1);
}

t_quaternion	q_mul(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	ret;

	ret.r = q1.r * q2.r - q1.i * q2.i - q1.j * q2.j - q1.k * q2.k;
	ret.i = q1.r * q2.i + q1.i * q2.r + q1.j * q2.k - q1.k * q2.j;
	ret.j = q1.r * q2.j + q1.j * q2.r + q1.k * q2.i - q1.i * q2.k;
	ret.k = q1.r * q2.k + q1.k * q2.r + q1.i * q2.j - q1.j * q2.i;
	return (ret);
}

double	q_dot(t_quaternion q1, t_quaternion q2)
{
	return (q1.r * q2.r + q1.i * q2.i + q1.j * q2.j + q1.k * q2.k);
}

t_quaternion	q_scale(t_quaternion q1, double s)
{
	q1.r *= s;
	q1.i *= s;
	q1.j *= s;
	q1.k *= s;
	return (q1);
}
