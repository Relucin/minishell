/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 13:21:15 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/26 16:31:14 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftlist.h>
#include <unistd.h>
#include <ftstdio.h>
#include <ftstring.h>
#include <stdlib.h>
#include <minishell.h>

void	ms_env_update(char *var, char *value, t_list **my_environ)
{
	char	*targs[3];

	targs[0] = var;
	targs[1] = value;
	targs[2] = 0;
	ms_setenv(targs, my_environ);
}

char	*ms_env_search(char *var, t_list *my_environ)
{
	size_t	len;

	len = ft_strlen(var);
	while (my_environ)
	{
		if (!ft_strncmp(my_environ->content, var, len))
			return (my_environ->content + len);
		my_environ = my_environ->next;
	}
	return (0);
}

void	ms_exec(char *fpath, char **args, char **env)
{
	pid_t	pid;
	int		stat_loc;

	pid = fork();
	if (pid > 0)
	{
		while (1)
		{
			waitpid(pid, &stat_loc, WUNTRACED);
			if (!WIFEXITED(stat_loc) || !WIFSIGNALED(stat_loc))
				break ;
		}
	}
	else if (!pid)
	{
		execve(fpath, args, env);
		ft_dprintf(2, "minishell: error executing: %s\n", args[0]);
		exit(EXIT_FAILURE);
	}
	else
		ft_dprintf(2, "minishell: error forking\n");
}

char	**ms_list_2darr(t_list *lst)
{
	t_list	*tmp;
	char	**ret;
	int		len;

	len = 0;
	tmp = lst;
	while (tmp)
	{
		++len;
		tmp = tmp->next;
	}
	ret = malloc(sizeof(*ret) * (len + 1));
	len = 0;
	while (lst)
	{
		ret[len++] = lst->content;
		lst = lst->next;
	}
	ret[len] = 0;
	return (ret);
}

int		ms_currentpath(char **args, t_list *my_environ)
{
	char	**env;
	int		ret;

	if (!(ret = access(args[0], F_OK | R_OK)))
	{
		if (!access(args[0], X_OK))
		{
			env = ms_list_2darr(my_environ);
			ms_exec(args[0], args, env);
			free(env);
		}
		else
			ft_dprintf(2, "minishell: permission denied: %s\n", args[0]);
	}
	return (!ret);
}
