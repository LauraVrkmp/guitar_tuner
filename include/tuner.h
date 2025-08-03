/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tuner.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lveerkam <lveerkam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 19:42:38 by lveerkam      #+#    #+#                 */
/*   Updated: 2025/08/03 18:00:21 by lveerkam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUNER_H
# define TUNER_H

# define SAMPLE_RATE 48000
# define CHANNELS 1
# define BUFFER_DUR_MSEC 50
# define BUFFER_SIZE (SAMPLE_RATE * BUFFER_DUR_MSEC / 1000)
# define HOP_SIZE 512
# define YIN_THRESHOLD 0.15f
# define DIMENSIONS 600

# define WIN32_LEAN_AND_MEAN
# define NOGDI
# define NOUSER
# define NOMINMAX
# include "miniaudio.h"

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || defined(__MINGW64__)
#  include "../lib/raylib-windows/raylib-5.5_win64_mingw-w64/include/raylib.h"
# else
#  include <raylib.h>
# endif

typedef struct s_context
{
	ma_device	*device;
}	t_context;

typedef struct s_capture_state
{
	float	buffer[BUFFER_SIZE];
	int		index;
}	t_capture_state;

typedef struct s_setup
{
	ma_device_config	config;
	ma_result			result;
	ma_device			device;
	t_capture_state		state;
	t_context			context;
	float				buffer_copy[BUFFER_SIZE];
	int					start_index;
}	t_setup;

typedef struct	s_loop_vars
{
	int		ready;
	int		initialized;
	int		last_detection_index;
	int		samples_since_last;
	float	smoothed_freq;
}	t_loop_vars;

extern t_setup	*g_context_ptr;

void	handle_sigint(int sig);
void	sleep_ms(int ms);
float	detect_frequency(const float *buffer, int buffer_size,
						int sample_rate);
int		ready_capture(t_setup *setup, int initialized, float *smoothed_freq);

#endif