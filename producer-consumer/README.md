# Producer-consumer problem

This is one of the possible solutions to the Dijkstra's [producer-consumer problem](https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem) implemented in C. It uses two POSIX semaphores and a mutex to synchronize threads. Whenever the buffer is full, the producer thread goes to sleep until producer thread wakes it up. Whenever the buffer is empty, the consumer thread goes to sleep until producer thread wakes it up. All buffer operations are wrapped in mutex to avoid race conditions.
