/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapurro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 22:33:54 by pcapurro          #+#    #+#             */
/*   Updated: 2023/03/27 22:33:55 by pcapurro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# include "structures.h"

int					main(int argc, char **argv);

char				**ft_clean_input(int argc, char **argv);
void				*ft_init_struct(t_info *m_str, char **args);

int					ft_init_philo_life(t_info *m_str);
int					ft_start_philo_life(t_info *m_str);

void				ft_destroy_everything(t_info *m_str);
void				ft_destroy_last_things(t_info *m_str, int i);

void				*ft_philosophize(void *old_philo_str);

void				ft_take_forks(t_philo_info *philo_str);
void				ft_eat(t_philo_info *philo_str);
void				ft_sleep(t_philo_info *philo_str);
void				ft_think(t_philo_info *philo_str);

int					ft_init_sim(t_info *m_str);
int					ft_detach_philos(t_info *m_str, pthread_t *philo_ids);
int					ft_monitor_sim(t_info *m_str, pthread_t *philo_ids);
int					ft_monitor_out(t_info *m_str);

int					ft_init_philo_data(t_info *m_str);
void				*ft_init_philo_strs(t_info *m_str);
void				*ft_init_mutex_table(t_info *m_str);

time_t				ft_get_actual_time(void);
void				ft_starve_if_necessary(t_philo_info *philo_str);
int					ft_print_state_change(t_philo_info *philo_str, int nb);
int					ft_freeze_thread(t_philo_info *m_str, int time);
int					ft_all_knowing_checker(t_info *m_str);
int					ft_simulation_state(t_philo_info *philo_str);
void				ft_release_forks(t_philo_info *philo_str);

int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strdup(char *str);
void				ft_putstr_fd(char *s, int fd);
int					ft_atoi(const char *s);

char				**ft_split(char *s, char c);
int					ft_dstrlen(char **str);
void				ft_free_double(char **str);

void				*ft_print_malloc_error(void);
void				*ft_print_function_error(void);

#endif