/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:12:39 by vrybalko          #+#    #+#             */
/*   Updated: 2017/03/19 17:51:13 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		reduction(double a[3][6], int size, int pivot, int col)
{
	int		i;
	int		j;
	double	factor;

	factor = a[pivot][col];
	i = -1;
	while (++i < 2 * size)
		a[pivot][i] /= factor;
	i = -1;
	while (++i < size)
		if (i != pivot)
		{
			factor = a[i][col];
			j = -1;
			while (++j < 2 * size)
				a[i][j] -= a[pivot][j] * factor;
		}
}

t_mat		copy_array(double a[3][6])
{
	int		i;
	int		j;
	t_mat	res;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == 3 && i == 3)
				res.m[i][j] = 1;
			else if (i == 3 || j == 3)
				res.m[i][j] = 0;
			else
				res.m[i][j] = a[i][j];
		}
	}
	return (res);
}

t_mat		mat_inverse(t_mat a)
{
	int			i;
	int			j;
	double		res[3][6];

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 6)
		{
			if (j < 3)
				res[i][j] = a.m[i][j];
			else if (j == i + 3)
				res[i][j] = 1;
			else
				res[i][j] = 0;
		}
	}
	i = -1;
	while (++i < 3)
		reduction(res, 3, i, i);
	return (copy_array(res));
}

t_mat		mat_mul(t_mat a, t_mat b)
{
	t_mat	res;
	int		i;
	int		j;
	int		k;
	double	sum;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			sum = 0;
			k = -1;
			while (++k < 4)
				sum += a.m[i][k] * b.m[k][j];
			res.m[i][j] = sum;
		}
	}
	return (res);
}

t_mat		new_mat_ang_x(double ang)
{
	t_mat	new;

	new.m[0][0] = 1;
	new.m[0][1] = 0;
	new.m[0][2] = 0;
	new.m[0][1] = 0;
	new.m[0][3] = 0;
	new.m[1][0] = 0;
	new.m[1][1] = cos(ang);
	new.m[1][2] = sin(ang);
	new.m[1][3] = 0;
	new.m[2][0] = 0;
	new.m[2][1] = -sin(ang);
	new.m[2][2] = cos(ang);
	new.m[2][3] = 0;
	new.m[3][0] = 0;
	new.m[3][1] = 0;
	new.m[3][2] = 0;
	new.m[3][3] = 1;
	return (new);
}

t_mat		new_mat_ang_y(double ang)
{
	t_mat	new;

	new.m[0][0] = cos(ang);
	new.m[0][1] = 0;
	new.m[0][2] = sin(ang);
	new.m[0][1] = 0;
	new.m[0][3] = 0;
	new.m[1][0] = 0;
	new.m[1][1] = 1;
	new.m[1][2] = 0;
	new.m[1][3] = 0;
	new.m[2][0] = -sin(ang);
	new.m[2][1] = 0;
	new.m[2][2] = cos(ang);
	new.m[2][3] = 0;
	new.m[3][0] = 0;
	new.m[3][1] = 0;
	new.m[3][2] = 0;
	new.m[3][3] = 1;
	return (new);
}

t_mat		new_mat_ang_z(double ang)
{
	t_mat	new;

	new.m[0][0] = cos(ang);
	new.m[0][1] = -sin(ang);
	new.m[0][2] = 0;
	new.m[0][3] = 0;
	new.m[1][0] = sin(ang);
	new.m[1][1] = cos(ang);
	new.m[1][2] = 0;
	new.m[1][3] = 0;
	new.m[2][0] = 0;
	new.m[2][1] = 0;
	new.m[2][2] = 1;
	new.m[2][3] = 0;
	new.m[3][0] = 0;
	new.m[3][1] = 0;
	new.m[3][2] = 0;
	new.m[3][3] = 1;
	return (new);
}

t_mat		new_mat1(t_v3d x)
{
	t_mat	new;

	new.m[0][0] = x.x;
	new.m[0][1] = 0;
	new.m[0][2] = 0;
	new.m[0][3] = 0;
	new.m[1][0] = x.y;
	new.m[1][1] = 0;
	new.m[1][2] = 0;
	new.m[1][3] = 0;
	new.m[2][0] = x.z;
	new.m[2][1] = 0;
	new.m[2][2] = 0;
	new.m[2][3] = 0;
	new.m[3][0] = 1;
	new.m[3][1] = 0;
	new.m[3][2] = 0;
	new.m[3][3] = 0;
	return (new);
}

t_mat		new_mat(t_v3d x, t_v3d y, t_v3d z)
{
	t_mat	new;

	new.m[0][0] = y.x;
	new.m[0][1] = z.x;
	new.m[0][2] = x.x;
	new.m[0][3] = 0;
	new.m[1][0] = y.y;
	new.m[1][1] = z.y;
	new.m[1][2] = x.y;
	new.m[1][3] = 0;
	new.m[2][0] = y.z;
	new.m[2][1] = z.z;
	new.m[2][2] = x.z;
	new.m[2][3] = 0;
	new.m[3][0] = 0;
	new.m[3][1] = 0;
	new.m[3][2] = 0;
	new.m[3][3] = 1;
	return (new);
}

t_p3d		rot_p(t_p3d p, t_v3d ang, t_p3d center)
{
	t_mat	m;

	m = mat_mul(new_mat_ang_x(ang.x), new_mat_ang_y(ang.y));
	m = mat_mul(m, new_mat_ang_z(ang.z));
	m = mat_mul(new_mat1(new_v3d(p.x - center.x, p.y - center.y,
		p.z - center.z)), m);
	return (new_p3d(m.m[0][0] + center.x, m.m[1][0] + center.y,
		m.m[2][0] + center.z));
}
