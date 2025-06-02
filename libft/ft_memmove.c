/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 16:30:17 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 19:24:53 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*p;
	const char	*s;

	if (!dest && !src)
		return (NULL);
	p = (char *)dest;
	s = (const char *)src;
	if (s > p)
	{
		while (n-- > 0)
			*p++ = *s++;
	}
	else
	{
		p = p + n;
		s = s + n;
		while (n-- > 0)
			*(--p) = *(--s);
	}
	return (dest);
}
