/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 20:19:28 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/26 17:02:56 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstdio.h>
#include <ftstring.h>
#include <stdlib.h>
#include <unistd.h>
#include <minishell.h>

static char	**ms_get_path(t_list *my_environ)
{
	char	**path;

	path = 0;
	while (my_environ)
	{
		if (!ft_strncmp(my_environ->content, "PATH=", 5))
		{
			path = ft_strsplit((my_environ->content) + 5, ':');
			break ;
		}
		my_environ = my_environ->next;
	}
	return (path);
}

static int	ms_path_find(char *path, char **args, t_list *my_environ)
{
	char	*fpath;
	char	**env;
	int		ret;

	ft_asprintf(&fpath, "%s/%s", path, args[0]);
	if (!(ret = access(fpath, F_OK | R_OK)))
	{
		if (!access(fpath, X_OK))
		{
			env = ms_list_2darr(my_environ);
			ms_exec(fpath, args, env);
			free(env);
		}
		else
			ft_dprintf(2, "minishell: permission denied: %s\n", args[0]);
	}
	free(fpath);
	return (!ret);
}

int			ms_path_check(char **args, t_list *my_environ)
{
	char	**path;
	int		i;
	int		ti;

	i = 0;
	if ((path = ms_get_path(my_environ)))
	{
		while (path[i] && !ms_path_find(path[i], args, my_environ))
			++i;
		i = (int)path[i];
	}
	else
		return (0);
	ti = 0;
	while (path[ti])
		free(path[ti++]);
	free(path);
	return (i);
}
