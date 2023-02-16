/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env_hashtable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:39:47 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/16 13:47:15 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_env_variables(char **envp)
{
	if (*envp)
	{
		insert_in_hashtable(*envp);
		store_env_variables(envp + 1);
	}
}
