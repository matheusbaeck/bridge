/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baeck <baeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:42:31 by baeck             #+#    #+#             */
/*   Updated: 2024/01/03 18:05:05 by baeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bridge.h"

void	close_pipes(int ***fd, int i, int end)
{
	--i;
	while (++i < end)
	{
		if ((*fd)[i][0] > 0)
			close((*fd)[i][0]);
		if ((*fd)[i][1] > 0)
			close((*fd)[i][1]);
	}
}

void	fd_swap(int *fd1, int *fd2)
{
	int	temp;

	temp = *fd1;
	*fd1 = *fd2;
	*fd2 = temp;
}
