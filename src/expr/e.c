/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:15:49 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 13:16:41 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "shell.h"

int	expr_e(t_shell *shell, char **args)
{
	(void)shell;
	return (access(args[1], F_OK));
}
