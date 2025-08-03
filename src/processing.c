/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processing.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lveerkam <lveerkam@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/01 20:27:06 by lveerkam      #+#    #+#                 */
/*   Updated: 2025/08/03 14:11:09 by lveerkam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tuner.h"

static float	*edit_diff(float *diff, int max_tau)
{
	float	running_sum;
	int		tau;

	running_sum = 0.f;
	diff[0] = 1.f;
	tau = 1;
	while (tau < max_tau)
	{
		running_sum += diff[tau];
		diff[tau] *= tau / running_sum;
		tau++;
	}
	return (diff);
}

static float	*fill_diff(int max_tau, const float *buffer, float *diff)
{
	int		tau;
	int		i;
	float	sum;
	float	delta;

	tau = 0;
	while (tau < max_tau)
	{
		sum = 0.f;
		i = 0;
		while (i < max_tau)
		{
			delta = buffer[i] - buffer[i + tau];
			sum += delta * delta;
			i++;
		}
		diff[tau] = sum;
		tau++;
	}
	diff = edit_diff(diff, max_tau);
	return (diff);
}

static int	estimate_tau(float *diff, int max_tau)
{
	int	tau_estimate;
	int	tau;

	tau_estimate = -1;
	tau = 2;
	while (tau < max_tau)
	{
		if (diff[tau] < YIN_THRESHOLD)
		{
			while ((tau + 1) < max_tau && diff[tau + 1] < diff[tau])
				tau++;
			tau_estimate = tau;
			break ;
		}
		tau++;
	}
	return (tau_estimate);
}

static float	improve_tau(int tau_estimate, float *diff, int max_tau)
{
	int		x0;
	int		x2;
	float	s0;
	float	s1;
	float	s2;

	if (tau_estimate < 1)
		x0 = tau_estimate;
	else
		x0 = tau_estimate - 1;
	if ((tau_estimate + 1) < max_tau)
		x2 = tau_estimate + 1;
	else
		x2 = tau_estimate;
	s0 = diff[x0];
	s1 = diff[tau_estimate];
	s2 = diff[x2];
	return (tau_estimate + (s2 - s0) / (2 * (2 * s1 - s2 - s0)));
}

float	detect_frequency(const float *buffer, int buffer_size,
	int sample_rate)
{
	int		max_tau;
	int		tau_estimate;
	float	*diff;
	float	better_tau;
	float	frequency;

	max_tau = buffer_size / 2;
	diff = malloc(sizeof(float) * max_tau);
	diff = fill_diff(max_tau, buffer, diff);
	tau_estimate = estimate_tau(diff, max_tau);
	if (tau_estimate == -1)
	{
		free(diff);
		return (-1.f);
	}
	better_tau = improve_tau(tau_estimate, diff, max_tau);
	frequency = sample_rate / better_tau;
	free(diff);
	return (frequency);
}
