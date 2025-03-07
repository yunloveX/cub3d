/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quatlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:45:20 by iestero-          #+#    #+#             */
/*   Updated: 2025/02/14 10:45:23 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATLIB_H
# define QUATLIB_H

# include <math.h>

typedef struct s_quaternion
{
	double	r;
	double	i;
	double	j;
	double	k;
}				t_quaternion;

/*quat_ops1.c*/
t_quaternion	q_add(t_quaternion q1, t_quaternion q2);
t_quaternion	q_sub(t_quaternion q1, t_quaternion q2);
t_quaternion	q_mul(t_quaternion q1, t_quaternion q2);
double			q_dot(t_quaternion q1, t_quaternion q2);
t_quaternion	q_scale(t_quaternion q1, double s);

/*quat_ops2.c*/
void			q_zero(t_quaternion *q);
t_quaternion	q_conj(t_quaternion q);
double			q_norm(t_quaternion q);
void			q_normalize(t_quaternion *q);
t_quaternion	q_rotate(t_quaternion p, t_quaternion rot);

/*quat_ops3.c*/
t_quaternion	q_gaps(t_quaternion point, t_quaternion dir);

#endif
