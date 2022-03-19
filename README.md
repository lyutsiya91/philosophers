# philosophers
This project is a training to multi-threads/multi-process programming with the use of mutex and semaphore.

• One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
• The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
• There are also forks on the table. There are as many forks as philosophers.
• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
• When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
• Every philosopher needs to eat and should never starve.
• Philosophers don’t speak with each other.
• Philosophers don’t know if another philosopher is about to die.
• No need to say that philosophers should avoid dying!

The programs take the following arguments: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: is the number of philosophers and also the number
of forks

◦ time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting his last meal or the beginning of the simulation, it
dies

◦ time_to_eat: is in milliseconds and is the time it takes for a philosopher to
eat. During that time he will need to keep the two forks.

◦ time_to_sleep: is in milliseconds and is the time the philosopher will spend
sleeping.

◦ number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.

• Each philosopher should be given a number from 1 to ’number_of_philosophers’.

• Philosopher number 1 is next to philosopher number ’number_of_philosophers’.
Any other philosopher with number N is seated between philosopher N - 1 and
philosopher N + 1

• Any change of status of a philosopher must be written as follows (with X replaced
with the philosopher number and timestamp_in_ms the current timestamp in milliseconds)
◦ timestamp_in_ms X has taken a fork  
◦ timestamp_in_ms X is sleeping  
◦ timestamp_in_ms X is thinking  
◦ timestamp_in_ms X died  

• The status printed should not be scrambled or intertwined with another philosopher’s status.

• You can’t have more than 10 ms between the death of a philosopher and when it
will print its death.

• Again, philosophers should avoid to die!
