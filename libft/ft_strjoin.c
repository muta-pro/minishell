/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 15:50:21 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 19:27:38 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*res;
	char	*start;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(len + 1);
	if (res == NULL)
		return (NULL);
	start = res;
	while (*s1)
	{
		*res = *s1;
		res++;
		s1++;
	}
	while (*s2)
	{
		*res = *s2;
		res++;
		s2++;
	}
	*res = '\0';
	return (start);
}
