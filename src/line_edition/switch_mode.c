/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 13:37:50 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/27 17:11:03 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>

#include "fill_line.h"
#include "libft.h"

int	ft_paste(t_shell *shell)
{
	if (shell->pbpaste)
		ft_addchar(shell, shell->pbpaste, 0);
	return (0);
}
