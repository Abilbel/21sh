/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 09:04:48 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/30 16:50:54 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

t_var		*copy_env(const char **env)
{
	t_var	*res;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		if (set_var_full(&res, env[i], 1))
		{
			free_vars(&res);
			return (NULL);
		}
		++i;
	}
	return (res);
}

static void	copy_content(t_var *new_var, t_var *old_var)
{
	new_var->exported = old_var->exported;
	new_var->len_name = old_var->len_name;
	new_var->len_value = old_var->len_value;
	new_var->alloc_size = ft_strlen(old_var->var);
}

t_var		*copy_vars(t_var *vars, int only_exported)
{
	t_var	*copy;
	t_var	*new_var;

	copy = NULL;
	while (vars)
	{
		if ((only_exported && vars->exported) || !only_exported)
		{
			if (!(new_var = malloc(sizeof(*new_var))))
				return (free_vars(&copy));
			if (!(new_var->var = ft_strdup(vars->var)))
			{
				free(new_var);
				free_vars(&copy);
				return (NULL);
			}
			new_var->next = NULL;
			copy_content(new_var, vars);
			add_to_vars(&copy, new_var);
		}
		vars = vars->next;
	}
	return (copy);
}

t_var		*free_vars(t_var **vars)
{
	t_var			*next;
	t_var			*iter;

	iter = *vars;
	while (iter)
	{
		next = iter->next;
		free(iter->var);
		free(iter);
		iter = next;
	}
	*vars = NULL;
	return (NULL);
}
