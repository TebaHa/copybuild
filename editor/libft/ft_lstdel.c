/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:50:31 by djast             #+#    #+#             */
/*   Updated: 2018/12/13 14:02:15 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*cur_lst;
	t_list	*nxt_lst;

	if (alst == NULL || del == NULL)
		return ;
	cur_lst = *alst;
	if (cur_lst == NULL)
		return ;
	while (cur_lst != NULL)
	{
		nxt_lst = cur_lst->next;
		ft_lstdelone(&cur_lst, del);
		cur_lst = nxt_lst;
	}
	*alst = NULL;
}
