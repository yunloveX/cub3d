/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_ops2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:48:14 by fsusanna          #+#    #+#             */
/*   Updated: 2025/02/12 09:30:16 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quatlib.h"

void	q_zero(t_quaternion *q)
{
	q->r = 0.0;
	q->i = 0.0;
	q->j = 0.0;
	q->k = 0.0;
}

t_quaternion	q_conj(t_quaternion q)
{
	q.i *= -1.0;
	q.j *= -1.0;
	q.k *= -1.0;
	return (q);
}

double	q_norm(t_quaternion q)
{
	return (sqrt(q_dot(q, q)));
}

void	q_normalize(t_quaternion *q)
{
	if (q->r || q->i || q->j || q->k)
		*q = q_scale(*q, 1 / q_norm(*q));
}

t_quaternion	q_rotate(t_quaternion p, t_quaternion rot)
{
	p = q_mul(rot, p);
	p = q_mul(p, q_conj(rot));
	return (p);
}
