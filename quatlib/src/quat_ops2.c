/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cloud.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsusanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:48:14 by fsusanna          #+#    #+#             */
/*   Updated: 2023/02/20 19:42:42 by fsusanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quatlib.h"

t_quaternion	q_conj(t_quaternion q)
{
	q.i *= -1.0;
	q.j *= -1.0;
	q.k *= -1.0;
	return (q);
}

double	q_norm(t_quaternion q)
{
	return (pow(q_dot(q, q), -0.5));
}

void	q_normalize(t_quaternion *q)
{
	*q = q_scale(*q, q_norm(*q));
}

t_quaternion	q_rotate(t_quaternion p, t_quaternion rot)
{
	p = q_mul(rot, p);
	p = q_mul(p, q_conj(rot));
	return (p);
}
