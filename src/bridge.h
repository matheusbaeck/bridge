/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baeck <baeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 02:00:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/01/03 18:18:16 by baeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRIDGE_H
# define BRIDGE_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h> 
# include <errno.h>

enum e_bridge
{
    SUCCESS = 1,
    FAILURE = 0
};

typedef struct s_bridge
{
    int         fd_infile;
    int         fd_outfile;
    int	        size;
    int         (*init)(void *param);
    void        *param;
}               t_bridge;

typedef struct s_block
{
    int     (*task)(void *, t_bridge *);
    int     (*error_handler)(int);
    void    *param;
}           t_block;

//utils
void	close_pipes(int ***fd, int i, int end);
void	fd_swap(int *fd1, int *fd2);

#endif