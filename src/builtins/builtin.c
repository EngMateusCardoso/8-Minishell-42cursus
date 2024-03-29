/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:32:35 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/23 12:58:27 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	run_builtin(char **command, int isfork)
{
	if (isfork)
	{
		if (!ft_strncmp(command[0], "echo", 5))
			echo_builtin(command);
		else if (!ft_strncmp(command[0], "pwd", 4))
			pwd_builtin();
		else if (!ft_strncmp(command[0], "env", 4))
			env_builtin();
	}
	else
	{
		if (!ft_strncmp(command[0], "cd", 3))
			cd_builtin(command);
		else if (!ft_strncmp(command[0], "export", 7))
			export_builtin(command);
		else if (!ft_strncmp(command[0], "unset", 6))
			unset_builtin(command);
		else if (!ft_strncmp(command[0], "exit", 5))
			exit_builtin(command);
	}
}

int	is_builtin(char *command)
{
	if (!ft_strncmp(command, "echo", 5) || !ft_strncmp(command, "cd", 3) || \
		!ft_strncmp(command, "pwd", 4) || !ft_strncmp(command, "export", 7) \
		|| !ft_strncmp(command, "unset", 6) || !ft_strncmp(command, "env", 4) \
		|| !ft_strncmp(command, "exit", 5))
		return (1);
	return (0);
}

int	check_identifier(char *var)
{
	int		i;
	int		flag;
	char	mark;

	i = 0;
	mark = 0;
	flag = 0;
	if (var == NULL || var[i] == '\0' || var[i] == '=')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (ft_isalpha(var[i]) || var[i] == '_')
			flag = 1;
		if (ft_isdigit(var[i]) && !flag)
			return (0);
		if ((var[i] == '\'' || var[i] == '\"') && !mark)
			mark = var[i];
		else if (var[i] == mark)
			mark = 0;
		else if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	identifier_error(char *cmd, char *value)
{
	char	*tmp;
	char	*tmp2;

	if (value)
	{
		tmp = ft_strjoin(cmd, ": `");
		tmp2 = ft_strjoin(tmp, value);
		error_msg(tmp2, "': not a valid identifier", 1);
		ft_free_pointer((void *)&tmp);
		ft_free_pointer((void *)&tmp2);
	}
	else
		error_msg(cmd, ": `': not a valid identifier", 1);
}

void	error_handler(char *str1, char *str2, int status, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	perror("");
	g_data.exit_code = status;
}
