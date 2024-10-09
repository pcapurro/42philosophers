# Philosophers
### « I never thought philosophy would be so deadly »

This project consists in a simulation of philosophers (each being represented by a thread) executing a simple routine: take two forks, eat, sleep and think.
The routine can be executed forever, but the simulation stops if a philosopher dies or if all the philosophers ate the specified number of meals.

Semaphores, Mutex and Barriers are also used, mainly for thread synchronisation but also to avoid data races.

Logs are displayed during the simulation, in the following format:
[actual timestamp]* [philosopher id] [action]
__Example__ : "410 2 is thinking"

All the paramaters of the simulation can be set by the user.

__Usage__: ./philo [number of philosophers] [time to die] [time to eat] [time to sleep] ([meals number])
Time values are in milliseconds and can't exceed 60. Last argument is optionnal.
