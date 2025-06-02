/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 15:34:22 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 19:28:59 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	while (len-- > 0 && s[i + start] != '\0')
	{
		i++;
	}
	s += start;
	res = malloc(i + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s, i + 1);
	return (res);
}
