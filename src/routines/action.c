/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiacom <engiacom@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:23:45 by engiacom          #+#    #+#             */
/*   Updated: 2025/04/29 15:23:47 by engiacom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	slash(t_philo **tmp)
{
	if (!check_finish_and_unlock(tmp))
		return (0);
	print_status(tmp, "is eating");
	mutex_last_meal(*tmp);
	usleep((*tmp)->table->rules.time_to_eat * 1000);
	mutex_meals(*tmp);
	pthread_mutex_unlock((*tmp)->r_forks);
	pthread_mutex_unlock((*tmp)->l_forks);
	if (!check_finish(tmp))
		return (0);
	print_status(tmp, "is sleeping");
	usleep((*tmp)->table->rules.time_to_sleep * 1000);
	return (1);
}

void	last_odd(t_philo **tmp)
{
	pthread_mutex_lock(&(*tmp)->meal_mutex);
	if ((*tmp)->meals == 0)
		print_status(tmp, "is thinking");
	pthread_mutex_unlock(&(*tmp)->meal_mutex);
	pthread_mutex_lock((*tmp)->l_forks);
	print_status(tmp, "has taken a fork");
	pthread_mutex_lock((*tmp)->r_forks);
	print_status(tmp, "has taken a fork");
	if (!slash(tmp))
		return ;
	pthread_mutex_lock(&(*tmp)->meal_mutex);
	if ((*tmp)->meals != 0 && (*tmp)->meals != (*tmp)->table->rules.number_eat)
		print_status(tmp, "is thinking");
	pthread_mutex_unlock(&(*tmp)->meal_mutex);
	if ((*tmp)->table->rules.philos % 2 == 1)
		usleep(((*tmp)->table->rules.time_to_eat) * 1000);
}

void	last_even(t_philo **tmp)
{
	if ((*tmp)->meals == 0 && (*tmp)->table->rules.philos > 1)
		usleep(((*tmp)->table->rules.time_to_eat * 1000) + 1000);
	pthread_mutex_lock(&(*tmp)->meal_mutex);
	if ((*tmp)->meals == 0)
		print_status(tmp, "is thinking");
	pthread_mutex_unlock(&(*tmp)->meal_mutex);
	pthread_mutex_lock((*tmp)->r_forks);
	print_status(tmp, "has taken a fork");
	pthread_mutex_lock(&(*tmp)->table->finish_mutex);
	if (!check_solo(tmp))
		return ;
	pthread_mutex_unlock(&(*tmp)->table->finish_mutex);
	pthread_mutex_lock((*tmp)->l_forks);
	print_status(tmp, "has taken a fork");
	if (!slash(tmp))
		return ;
	pthread_mutex_lock(&(*tmp)->meal_mutex);
	if ((*tmp)->meals != 0 && (*tmp)->meals != (*tmp)->table->rules.number_eat)
		print_status(tmp, "is thinking");
	pthread_mutex_unlock(&(*tmp)->meal_mutex);
	if ((*tmp)->meals != (*tmp)->table->rules.number_eat)
		usleep(((*tmp)->table->rules.time_to_eat) * 1000);
}

void	odd(t_philo **tmp)
{
	pthread_mutex_lock(&(*tmp)->meal_mutex);
	if ((*tmp)->meals == 0)
		print_status(tmp, "is thinking");
	pthread_mutex_unlock(&(*tmp)->meal_mutex);
	pthread_mutex_lock((*tmp)->l_forks);
	print_status(tmp, "has taken a fork");
	pthread_mutex_lock((*tmp)->r_forks);
	print_status(tmp, "has taken a fork");
	if (!slash(tmp))
		return ;
	pthread_mutex_lock(&(*tmp)->meal_mutex);
	if ((*tmp)->meals != 0 && (*tmp)->meals != (*tmp)->table->rules.number_eat)
		print_status(tmp, "is thinking");
	pthread_mutex_unlock(&(*tmp)->meal_mutex);
	if ((*tmp)->table->rules.philos % 2 == 1
		&& (*tmp)->meals != (*tmp)->table->rules.number_eat)
		usleep(((*tmp)->table->rules.time_to_eat) * 1000);
}

void	even(t_philo **tmp)
{
	pthread_mutex_lock(&(*tmp)->meal_mutex);
	if ((*tmp)->meals == 0)
		print_status(tmp, "is thinking");
	pthread_mutex_unlock(&(*tmp)->meal_mutex);
	pthread_mutex_lock((*tmp)->r_forks);
	print_status(tmp, "has taken a fork");
	pthread_mutex_lock((*tmp)->l_forks);
	print_status(tmp, "has taken a fork");
	if (!slash(tmp))
		return ;
	pthread_mutex_lock(&(*tmp)->meal_mutex);
	if ((*tmp)->meals != 0 && (*tmp)->meals != (*tmp)->table->rules.number_eat)
		print_status(tmp, "is thinking");
	pthread_mutex_unlock(&(*tmp)->meal_mutex);
	if ((*tmp)->meals != 0 && (*tmp)->table->rules.philos % 2 == 1)
		usleep(((*tmp)->table->rules.time_to_eat) * 1000);
}
