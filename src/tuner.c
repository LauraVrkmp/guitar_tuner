/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tuner.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lveerkam <lveerkam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 19:42:33 by lveerkam      #+#    #+#                 */
/*   Updated: 2025/08/03 22:29:49 by lveerkam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define MA_IMPLEMENTATION

#include "../include/tuner.h"

t_setup	*g_context_ptr = NULL;

static void	data_callback(ma_device *pDevice, void *pOutput,
	const void *pInput, ma_uint32 frameCount)
{
	t_capture_state	*state;
	const float		*input;
	ma_uint32		i;

	state = (t_capture_state *)pDevice->pUserData;
	input = (const float *)pInput;
	i = 0;
	while (i < frameCount)
	{
		state->buffer[state->index] = input[i];
		state->index = (state->index + 1) % BUFFER_SIZE;
		i++;
	}
	(void)pOutput;
}

static void	init(t_setup *setup)
{
	int	i;

	setup->config = ma_device_config_init(ma_device_type_capture);
	setup->config.capture.format = ma_format_f32;
	setup->config.capture.channels = CHANNELS;
	setup->config.sampleRate = SAMPLE_RATE;
	setup->config.periodSizeInFrames = 256;
	setup->config.periods = 2;
	setup->config.dataCallback = data_callback;
	setup->state.index = 0;
	i = 0;
	while (i < (BUFFER_SIZE - 1))
		setup->state.buffer[i++] = 0.0f;
	setup->config.pUserData = &setup->state;
	g_context_ptr = setup;
	setup->context.device = &setup->device;
	signal(SIGINT, handle_sigint);
}

static int	service_start(t_setup *setup)
{
	setup->result = ma_device_init(NULL, &setup->config, &setup->device);
	if (setup->result != MA_SUCCESS)
	{
		//printf("Failed to initialize capture devide.\n");
		return (EXIT_FAILURE);
	}
	//printf("Starting recording..\n");
	setup->result = ma_device_start(&setup->device);
	if (setup->result != MA_SUCCESS)
	{
		//printf("Failed to start device.\n");
		ma_device_uninit(&setup->device);
		CloseWindow();
		return (EXIT_FAILURE);
	}
	return (0);
}

void	capture_loop(t_setup *setup)
{
	t_loop_vars	vars;

	vars.initialized = 0;
	vars.ready = 0;
	vars.last_detection_index = 0;
	vars.smoothed_freq = 0;
	while (!WindowShouldClose())
	{
		BeginDrawing();
		sleep_ms(BUFFER_DUR_MSEC);
		vars.samples_since_last = (setup->state.index + BUFFER_SIZE
				- vars.last_detection_index) % BUFFER_SIZE;
		if (vars.samples_since_last >= HOP_SIZE)
		{
			vars.ready = 1;
			vars.last_detection_index = setup->state.index;
		}
		else
			vars.ready = 0;
		if (vars.ready)
			vars.initialized = ready_capture(setup, vars.initialized,
					&vars.smoothed_freq);
		EndDrawing();
	}
}

int	main(void)
{
	t_setup	*setup;

	SetTraceLogLevel(LOG_NONE);
	InitWindow(DIMENSIONS, DIMENSIONS, "tuner");
	SetTargetFPS(60);
	setup = (t_setup *)malloc(sizeof(t_setup));
	if (setup == NULL)
		return (1);
	memset(setup, 0, sizeof(t_setup));
	init(setup);
	service_start(setup);
	//printf("Recording... Press Ctrl+C to stop.\n");
	capture_loop(setup);
	ma_device_uninit(&setup->device);
	free(setup);
	CloseWindow();
	return (0);
}
