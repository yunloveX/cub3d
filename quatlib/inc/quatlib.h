/* ************************************************************************** */
/*                                                             _____________  */
/*                                                            /            /| */
/*                                                           /____________/ | */
/*   quatlib.h                                               |     ____   | | */
/*                                                           |    /___/|  | | */
/*   By: github.com/JavierSusanna                            |    | Q ||  | | */
/*                                                           |    |___|/  | / */
/*   Created: 2024/09/13                                     |____________|/  */
/*   Updated: 2024/09/13                                                      */
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

#endif
