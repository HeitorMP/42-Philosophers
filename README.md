
# Philosophers (42 - lvl 3)

The dining philosopher's problem is the classical problem of synchronization which says that Five philosophers are sitting around a circular table and their job is to think and eat alternatively. A bowl of noodles is placed at the center of the table along with five chopsticks for each of the philosophers. To eat a philosopher needs both their right and a left chopstick. A philosopher can only eat if both immediate left and right chopsticks of the philosopher is available. In case if both immediate left and right chopsticks of the philosopher are not available then the philosopher puts down their (either left or right) chopstick and starts thinking again.



## What I've learned!

 - The basics of threading a process and Mutex.
 - That philosophers cannot eat with just one fork

## 42 Rules

- Global variables are forbidden!
-  Your(s) program(s) should take the following arguments:
    number_of_philosophers time_to_die time_to_eat time_to_sleep
    [number_of_times_each_philosopher_must_eat]
- number_of_philosophers: The number of philosophers and also the number of forks.
-  time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
    milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
    During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all
    philosophers have eaten at least number_of_times_each_philosopher_must_eat
    times, the simulation stops. If not specified, the simulation stops when a
    philosopher dies.
- Each philosopher has a number ranging from 1 to number_of_philosophers.
- Philosopher number 1 sits next to philosopher number number_of_philosophers.
    Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

###

• Any state change of a philosopher must be formatted as follows:
- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.

• A displayed state message should not be mixed up with another message.

• A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.

• Again, philosophers should avoid dying!

## Your program must not have any data races.
## Useful links:

[Threads](https://www.geeksforgeeks.org/multithreading-in-c/)
[Mutex](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)


