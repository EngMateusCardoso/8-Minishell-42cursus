/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:28:02 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/03 10:28:39 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

short int    is_redirection(char *token)
{
    if (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0 || \
        ft_strncmp(token, ">>", 2) == 0 || ft_strncmp(token, "<<", 2) == 0)
        return (1);
    return (0);
}
