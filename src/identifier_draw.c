/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   identifier_draw.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lveerkam <lveerkam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 22:25:42 by lveerkam      #+#    #+#                 */
/*   Updated: 2025/08/03 14:10:51 by lveerkam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tuner.h"

const char	*g_note_names[] = {
	"C", "C#", "D", "D#", "E", "F",
	"F#", "G", "G#", "A", "A#", "B"
};

static void	draw(int midi_rounded, double cents_off)
{
	const char	*line;
	int			text_width;

	line = TextFormat("Note: %s%d", g_note_names[midi_rounded % 12],
			midi_rounded / 12 - 1);
	text_width = MeasureText(line, 40);
	DrawText(line, (DIMENSIONS - text_width) / 2, (DIMENSIONS - 40) / 2 - 40,
		40, WHITE);
	DrawRectangle((DIMENSIONS - 2) / 2 + 32, (DIMENSIONS - 30) / 2 + 40, 2,
		40, RED);
	DrawRectangle((DIMENSIONS - 2) / 2 - 32, (DIMENSIONS - 30) / 2 + 40, 2,
		40, RED);
	DrawRectangle((DIMENSIONS - 4) / 2 + (cents_off * 4),
		(DIMENSIONS - 30) / 2 + 40, 4, 40, GREEN);
}

static int	identify_plus_draw(double freq)
{
	double		midi_exact;
	int			midi_rounded;
	double		cents_off;

	midi_exact = 69 + 12 * log2(freq / 440.0);
	midi_rounded = (int)round(midi_exact);
	cents_off = (midi_exact - midi_rounded) * 100;
	/* if (cents_off < -8)
		printf("Note is flat (%.2f Hz is -%.2f cents off %s%d)\n",
			freq, cents_off, g_note_names[midi_rounded % 12],
			midi_rounded / 12 - 1);
	else if (cents_off > 8)
		printf("Note is sharp (%.2f Hz is +%.2f cents off %s%d)\n",
			freq, cents_off, g_note_names[midi_rounded % 12],
			midi_rounded / 12 - 1);
	else
		printf("Note: %s%d (%.2f Hz, %.2f cents off)\n",
			g_note_names[midi_rounded % 12], midi_rounded / 12 - 1,
			freq, cents_off); */
	ClearBackground(BLACK);
	draw(midi_rounded, cents_off);
	return (1);
}

int	ready_capture(t_setup *setup, int initialized, float *smoothed_freq)
{
	int		i;
	float	freq;
	float	alpha;

	setup->start_index = setup->state.index % BUFFER_SIZE;
	i = 0;
	alpha = 0.2f;
	while (i < BUFFER_SIZE)
	{
		setup->buffer_copy[i] = setup->state.buffer[(setup->start_index + i)
			% BUFFER_SIZE];
		i++;
	}
	freq = detect_frequency(setup->buffer_copy, BUFFER_SIZE, SAMPLE_RATE);
	if (freq > 60 && freq < 1060)
	{
		if (!initialized)
			*smoothed_freq = freq;
		else
			*smoothed_freq = alpha * freq + (1.0f - alpha) * (*smoothed_freq);
		return (identify_plus_draw((double)(*smoothed_freq)));
	}
	return (0);
}
