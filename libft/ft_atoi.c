/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 18:43:05 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 19:21:27 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

int	ft_atoi(const char *nptr)
{
	long		res;
	int			i;
	int			sign;

	sign = 1;
	i = 0;
	res = 0;
	while ((nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		&& nptr[i] != '\0')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) && nptr[i] != '\0')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

long long	ft_atoll(const char *str)
{
	long long	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && (str[i] <= '\r')))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((sign == 1) && (res > (LLONG_MAX - (str[i] - '0')) / 10))
			return (LLONG_MAX);
		if ((sign == -1) && (-res < (LLONG_MIN + (str[i] - '0')) / 10))
			return (LLONG_MIN);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
