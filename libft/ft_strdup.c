/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 15:07:21 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 19:29:46 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*r;
	size_t	len;
	char	*start;

	len = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	r = malloc(len + 1);
	if (r == NULL)
		return (NULL);
	start = r;
	while (*s)
	{
		*r = *s;
		r++;
		s++;
	}
	*r = '\0';
	return (start);
}
