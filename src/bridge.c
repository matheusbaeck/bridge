/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baeck <baeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:36:25 by baeck             #+#    #+#             */
/*   Updated: 2024/01/03 18:05:41 by baeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bridge.h"

int	block_conect(t_bridge bridge, int ***fd, int i)
{
	if (i == 0)
	{
		if (*fd[2][0] > 0)
			fd_swap(fd[2][0], fd[0][0]);
		else
			return(perror("invalid file decriptor"), FAILURE);
	}
	if ((i + 1) == (bridge.size))
	{
		if (*fd[2][1] > 0)
			fd_swap(fd[2][1], fd[1][1]);
		else
			return(perror("invalid file decriptor"), FAILURE);
	}
	dup2(*fd[0][0], STDIN_FILENO);
	dup2(*fd[1][1], STDOUT_FILENO);
	close_pipes(fd, 0, 3);
	return (SUCCESS);
}

int block_exec(t_bridge *bridge, t_block block, int *status)
{
    if (!(bridge && block.task))
        return (FAILURE);
    if(status)
        *status = block.task(block.param, bridge);
    if (*(block.error_handler) != NULL)
    {
        if (status != NULL)
            return (block.error_handler(*status));
        else
            return (block.error_handler(block.task(block.param, bridge)));
    }
    else if (!status)
    {
        block.task(block.param, bridge);
        return (SUCCESS);
    }
    return (FAILURE);
}

int	main_process(int ***fd)
{
	int	*temp;

	close(*fd[0][0]);
	close(*fd[0][1]);
	temp = *fd[0];
	*fd[0] = *fd[1];
	*fd[1] = (int *)malloc(2 * sizeof(int));
	free(temp);
	if (pipe(*fd[1]) == -1)
		return (perror("invalid file decriptor"), FAILURE);
	return (SUCCESS);
}

void    bridge_init(t_bridge *self, t_bridge obj)
{
    *self = obj;
    if (self->init != NULL)
        (self->init)(self);
}

void bridge(t_bridge bridge, t_block block)
{
    t_bridge    *self;
    int     i;
    int     *status;
    int     **fd;
    pid_t   *pid_list;

    self = (t_bridge *) malloc(sizeof(t_bridge));
    bridge_init(self, bridge);
    i = -1;
    status = (int *) malloc(bridge.size * sizeof(int));
    fd = (int **) malloc (3 * sizeof(int *));
    while (++i < 3)
        fd[i] = (int *) malloc(2 * sizeof(int));
    pipe(fd[0]);
    pipe(fd[1]);
    fd[2][0] = bridge.fd_infile;
    fd[2][1] = bridge.fd_outfile;
    pid_list = (pid_t *) malloc(bridge.size * sizeof(pid_t));
    i = -1;
    while (++i < bridge.size)
    {
        pid_list[i] = fork();
        if (!pid_list[i])
        {
            /* block intern process */
            block_conect(*self, &fd, i);
            block_exec(self, block, &status[i]);
        }
        else
        {
            /* main process */
            main_process(&fd);
        }       
    }    
    /* wait all finish */
}

void    simple_bridge(int fd_in, int fd_out, int size, void *task, void *param)
{
    bridge((t_bridge){fd_in, fd_out, size, NULL, NULL}, (t_block){task, NULL, param});
}
