/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 16:17:17 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 19:24:46 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*p;
	const char	*s;

	if (!src && !dest)
		return (NULL);
	p = (char *)dest;
	s = (const char *)src;
	while (n-- > 0)
	{
		*p = *s;
		s++;
		p++;
	}
	return (dest);
}
