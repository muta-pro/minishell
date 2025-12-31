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

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((size_t)len + 1);
	if (!res)
		return (NULL);
	start = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	return (start);
}
