/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:09:42 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/26 14:35:09 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ftstring.h>
#include <minishell.h>
#define BUF 4096

static void		ms_parse_input(char *input, char ***args)
{
	char	**fargs;

	fargs = malloc(sizeof(*fargs) * ((ft_strlen(input) / 2) + 2));
	*args = fargs;
	while (*input)
	{
		while (*input && ft_strchr(" \n\t\e", *input))
			++input;
		if (*input == '\"')
		{
			*fargs++ = ++input;
			while (*input && *input != '\"')
				++input;
		}
		else if (*input)
		{
			*fargs++ = input;
			while (*input && !ft_strchr(" \n\t\e", *input))
				++input;
		}
		if (*input)
			*input++ = '\0';
	}
	*fargs = 0;
}

static void		ms_parse(char *input, t_list **my_environ)
{
	char		**ar;
	t_list		*tmp;
	int			i;

	i = 0;
	ms_parse_input(input, &ar);
	while (ar[i])
	{
		if (*ar[i] == '$')
		{
			tmp = *my_environ;
			while (tmp)
			{
				if (!ft_strncmp(tmp->content, ar[i] + 1, ft_strlen(ar[i] + 1)))
					ar[i] = tmp->content + ft_strlen(ar[i]);
				tmp = tmp->next;
			}
		}
		++i;
	}
	if (ar[0] && !ms_builtin_check(ar, my_environ))
		if (!ms_path_check(ar, *my_environ))
			if (!ms_currentpath(ar, *my_environ))
				ft_dprintf(2, "minishell: unknown command: %s \n", ar[0]);
	free(ar);
}

static t_list	*ms_create_env(void)
{
	extern char	**environ;
	t_list		*my_environ;

	my_environ = 0;
	while (*environ)
	{
		ft_lstadd(&my_environ, ft_lstnew(*environ, ft_strlen(*environ) + 1));
		++environ;
	}
	return (my_environ);
}

/*
** TODO: Free my_environ
*/

void			ms_loop(void)
{
	char		*input;
	int			rd;
	t_list		*my_environ;

	input = malloc(BUF);
	my_environ = ms_create_env();
	while (1)
	{
		ft_printf("minishell> ");
		rd = read(0, input, BUF);
		input[rd] = '\0';
		if (*input == '\n')
			continue ;
		else if (*input)
			ms_parse(input, &my_environ);
		else
			break ;
	}
	ft_printf("\n");
	free(input);
}

int				main(void)
{
	ms_loop();
	return (0);
}
