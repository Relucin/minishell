/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtinb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:34:42 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/26 18:20:41 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ftstdio.h>
#include <ftstring.h>
#include <stdlib.h>

void	ms_echo(char **args, t_list **my_environ)
{
	int	flag;

	(void)my_environ;
	if (*args && !ft_strcmp("-n", *args))
	{
		++args;
		flag = 0;
	}
	else
		flag = 1;
	while (*args)
	{
		ft_printf("%s", *args);
		if (args[1])
			ft_printf(" ");
		++args;
	}
	if (flag)
		ft_printf("\n");
}

void	ms_exit(char **args, t_list **my_environ)
{
	(void)args;
	(void)my_environ;
	exit(EXIT_FAILURE);
}

int		ms_builtin_check(char **args, t_list **my_environ)
{
	int			i;
	const char	*builtins[] = {"echo", "cd", "setenv",
								"unsetenv", "env", "exit", 0};
	static void	(*bi_funcs[])() = {&ms_echo, &ms_cd, &ms_setenv,
									&ms_unsetenv, &ms_env, &ms_exit};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(builtins[i], args[0]))
		{
			bi_funcs[i](args + 1, my_environ);
			break ;
		}
		++i;
	}
	return ((int)builtins[i]);
}
