/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 19:59:52 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 18:55:11 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*node;
	void	*content;

	if (!lst)
		return (NULL);
	res = NULL;
	while (lst)
	{
		if (f)
			content = f(lst->content);
		else
			content = lst->content;
		node = ft_lstnew(content);
		if (!node)
		{
			if (f)
				del(content);
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, node);
		lst = lst->next;
	}
	return (res);
}
