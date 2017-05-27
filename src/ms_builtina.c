/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtina.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:22:44 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/26 18:18:37 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ftstdio.h>
#include <ftstring.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

void		ms_cd(char **args, t_list **my_environ)
{
	char	old[PATH_MAX];
	char	new[PATH_MAX];
	char	*tmp;

	getcwd(old, PATH_MAX);
	if (!*args)
		(tmp = ms_env_search("HOME=", *my_environ)) ? ft_strcpy(new, tmp)
		: ft_strcpy(new, "/");
	else if (**args == '~' && (tmp = ms_env_search("HOME=", *my_environ)))
	{
		ft_strcpy(new, tmp);
		ft_strlcat(new, *args + 1, PATH_MAX);
	}
	else if (**args == '-' && (tmp = ms_env_search("OLDPWD=", *my_environ)))
		ft_strcpy(new, tmp);
	else
		ft_strcpy(new, *args);
	if (chdir(new))
		(!access(new, F_OK)) ? ft_dprintf(2, "cd: error: %s\n", new)
		: ft_dprintf(2, "cd: no such file or directory: %s\n", new);
	else
	{
		ms_env_update("OLDPWD", old, my_environ);
		ms_env_update("PWD", new, my_environ);
	}
}

void		ms_setenv(char **args, t_list **my_environ)
{
	t_list	*tmp;
	char	*tstr;

	tmp = *my_environ;
	if (!*args || ft_strrchr(*args, '='))
		ft_dprintf(2, "setenv: invalid variable name\n");
	else if (args[1] && !args[2])
	{
		ft_asprintf(&tstr, "%s=%s", args[0], args[1]);
		while (tmp && ft_strncmp(*args, tmp->content, ft_strlen(*args)))
			tmp = tmp->next;
		if (tmp)
			free(tmp->content);
		else
		{
			tmp = ft_lstnew(0, 0);
			ft_lstadd(my_environ, tmp);
		}
		tmp->content = tstr;
	}
	else
		ft_dprintf(2, "setenv: usage: [VARIABLE] [VALUE]\n");
}

void		ms_unsetenv(char **args, t_list **my_environ)
{
	t_list	*tmp;

	tmp = *my_environ;
	if (args[0] && !args[1])
	{
		while (tmp)
		{
			if (!ft_strncmp(*args, tmp->content, ft_strlen(*args)))
			{
				free(tmp->content);
				ft_lstdelnode(my_environ, tmp);
				ft_printf("%s\n", *args);
				break ;
			}
			tmp = tmp->next;
		}
		if (!tmp)
			ft_dprintf(2, "unsetenv: variable does not exist: %s\n", *args);
	}
	else
		ft_dprintf(2, "unsetenv: usage: [VARIABLE]\n");
}

static void	ms_env_printer(t_list *my_environ)
{
	ft_printf("%s\n", my_environ->content);
}

void		ms_env(char **args, t_list **my_environ)
{
	(void)args;
	ft_lstiter(*my_environ, &ms_env_printer);
}
