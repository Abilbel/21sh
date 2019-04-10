/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 08:16:59 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 08:44:43 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"

static char	**alloc_env(t_var *vars)
{
	char	**env;
	size_t	size_env;

	size_env = 0;
	while (vars)
	{
		if (vars->exported)
			++size_env;
		vars = vars->next;
	}
	if (!(env = malloc(sizeof(*env) * (size_env + 1))))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		return (NULL);
	}
	return (env);
}

static char	**clean_exit(char **env, int i)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
	while (i >= 0)
		free(env[i--]);
	free(env);
	return (NULL);
}

void		concat_var(t_var *var, const char *name, const char *value)
{
	int		i;

	i = 0;
	while (name[i])
	{
		var->var[i] = name[i];
		++i;
	}
	var->len_name = i;
	var->var[i] = '=';
	i = 0;
	while (value[i])
	{
		var->var[var->len_name + i + 1] = value[i];
		++i;
	}
	var->var[var->len_name + i + 1] = 0;
	var->len_value = i;
}

int			check_var(const char *name, const char *value)
{
	size_t	size_name;
	size_t	size_value;

	if ((size_name = ft_strlen(name)) > VAR_MAX)
	{
		ft_dprintf(STDERR_FILENO, "%s: variable name too long\n", EXEC_NAME);
		return (1);
	}
	else if ((size_value = ft_strlen(value)) > VAR_MAX)
	{
		ft_dprintf(STDERR_FILENO, "%s: variable content too long\n", EXEC_NAME);
		return (1);
	}
	return (0);
}

char		**build_env(t_var *vars, int copy)
{
	char	**env;
	int		i;

	if (!(env = alloc_env(vars)))
		return (NULL);
	i = 0;
	while (vars)
	{
		if (vars->exported)
		{
			if (copy)
			{
				if (!(env[i++] = ft_strdup(vars->var)))
					return (clean_exit(env, i - 1));
			}
			else
				env[i++] = vars->var;
		}
		vars = vars->next;
	}
	env[i] = NULL;
	return (env);
}
