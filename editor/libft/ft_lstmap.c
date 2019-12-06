/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 12:15:07 by djast             #+#    #+#             */
/*   Updated: 2018/12/18 15:30:53 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_del_lists(t_list *beg_lst)
{
	t_list	*cur_lst;

	cur_lst = beg_lst->next;
	while (cur_lst != NULL)
	{
		free(beg_lst);
		beg_lst = cur_lst;
		cur_lst = cur_lst->next;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*beg_lst;
	t_list	*cur_lst;
	t_list	*new_lst;

	beg_lst = NULL;
	while (lst != NULL)
	{
		if ((new_lst = f(lst)) != NULL)
		{
			if (beg_lst == NULL)
				beg_lst = new_lst;
			else
				cur_lst->next = new_lst;
			cur_lst = new_lst;
		}
		else
		{
			ft_del_lists(beg_lst);
			break ;
		}
		lst = lst->next;
	}
	return (beg_lst);
}
