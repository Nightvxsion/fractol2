/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcgar2 <marcgar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:23:14 by marcgar2          #+#    #+#             */
/*   Updated: 2025/03/18 22:23:14 by marcgar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	if (NULL == s1 || NULL == s2 || n <= 0)
		return (0);
	while (*s1 == *s2 && n > 0 && *s1 != '\0')
	{
		++s1;
		++s2;
		--n;
	}
	return (*s1 - *s2);
}

void	putstr_fd(char *s, int fd)
{
	if (NULL == s || fd < 0)
		return ;
	if (*s != '\0')
	{
		write(fd, s, 1);
		putstr_fd(s + 1, fd);
	}
}

double	atodbl(char *s)
{
	long	integer_part;
	double	fractional_part;
	double	pow;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	sign = +1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || 32 == *s)
		++s;
	while ('+' == *s || '-' == *s)
		if ('-' == *s++)
			sign = -sign;
	while (*s != '.' && *s)
		integer_part = (integer_part * 10) + (*s++ - '0');
	if ('.' == *s)
		++s;
	while (*s)
	{
		pow /= 10;
		fractional_part = fractional_part + (*s++ - '0') * pow;
	}
	return ((integer_part + fractional_part) * sign);
}

void	check_julia(t_fractal *fractal, char **argv, int argc)
{
	int	i;

	i = 0;
	fractal->name = argv[1];
	if ((argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0))
	{
		while (argv[2][i] != '\0' && argv[3][i] != '\0')
		{
			if (((argv[2][i] >= '0' && argv[2][i] <= '9')
				|| argv[2][i] == '.' || argv[2][i] == '-' || argv[2][i] == '+')
				&& ((argv[3][i] >= '0' && argv[3][i] <= '9')
				|| argv[3][i] == '.' || argv[3][i] == '-' || argv[3][i] == '+'))
			{
				fractal->julia_x = atodbl(argv[2]);
				fractal->julia_y = atodbl(argv[3]);
			}
			else
			{
				putstr_fd(ERROR_MESSAGE2, STDERR_FILENO);
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}
}
