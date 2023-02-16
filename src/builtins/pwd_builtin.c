/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:56:43 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/15 21:09:06 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_builtin(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		error_msg("pwd", "': couldn't find current path", 1);
	else
	{
		g_data.exit_code = 0;
		ft_putendl_fd(path, 1);
	}
	ft_free_pointer((void *)&path);
}
