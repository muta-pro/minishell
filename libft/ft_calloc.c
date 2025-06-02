/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/10 14:43:08 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 19:22:27 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	ts;
	void	*p;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (size <= SIZE_MAX / nmemb)
		ts = nmemb * size;
	else
		return (NULL);
	p = malloc(ts);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, ts);
	return (p);
}
