/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_sleep.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lveerkam <lveerkam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/02 12:12:46 by lveerkam      #+#    #+#                 */
/*   Updated: 2025/08/03 18:06:04 by lveerkam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tuner.h"

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# define NOGDI
# define NOUSER
# define NOMINMAX
# include <windows.h>

void	sleep_ms(int ms)
{
	Sleep(ms);
}
#endif

#ifndef _WIN32

void	sleep_ms(int ms)
{
	usleep(ms * 1000);
}
#endif

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_context_ptr != NULL)
	{
		ma_device_uninit(&g_context_ptr->device);
		free(g_context_ptr);
		g_context_ptr = NULL;
	}
	//printf("\nClean exit on Ctrl+C\n");
	exit(0);
}
