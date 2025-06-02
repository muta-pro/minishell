/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/11 15:53:15 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 19:23:59 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*itoajr(char *s, long nb, int sign);
static int	calcnumlen(long nb);
static char	*revstr(char *str);

char	*ft_itoa(int n)
{
	long	nb;
	int		sign;
	char	*res;

	sign = 0;
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		sign = 1;
	}
	res = malloc(calcnumlen(nb) + sign + 1);
	if (res == NULL)
		return (NULL);
	return (itoajr(res, nb, sign));
}

static int	calcnumlen(long nb)
{
	int	len;

	if (nb == 0)
		len = 1;
	else
		len = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static char	*itoajr(char *s, long nb, int sign)
{
	char	*start;

	start = s;
	if (nb == 0)
		*s++ = '0';
	else
	{
		while (nb > 0)
		{
			*s++ = (nb % 10) + '0';
			nb = nb / 10;
		}
	}
	if (sign == 1)
	{
		*s++ = '-';
	}
	*s = '\0';
	revstr(start);
	return (start);
}

static char	*revstr(char *str)
{
	int		len;
	int		i;
	char	ph;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	while (i < len / 2)
	{
		ph = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = ph;
		i++;
	}
	return (str);
}
