/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:10:02 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/14 22:01:57 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_builtin(void)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (i < TABLE_SIZE)
	{
		tmp = g_data.hash_table[i];
		while (tmp != NULL)
		{
			ft_putstr_fd(((t_env_var *)tmp->content)->key, 1);
			ft_putstr_fd("=", 1);
			if (((t_env_var *)(tmp->content))->value)
				ft_putstr_fd(((t_env_var *)(tmp->content))->value, 1);
			ft_putstr_fd("\n", 1);
			tmp = tmp->next;
		}
		i++;
	}
}
