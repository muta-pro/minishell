/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 14:11:10 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 19:28:44 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[j] != '\0' && j < len)
	{
		while (big[j] == little[i] && j < len)
		{
			j++;
			i++;
			if (little[i] == '\0')
				return ((char *)&big[j - i]);
		}
		j = j - i;
		i = 0;
		j++;
	}
	return (0);
}
