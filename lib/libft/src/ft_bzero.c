/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 09:37:55 by cvignal           #+#    #+#             */
/*   Updated: 2018/11/06 17:15:50 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	char *res;

	if (n == 0)
		return ;
	res = (char *)s;
	while (n--)
	{
		*res = 0;
		if (n)
			res++;
	}
}
