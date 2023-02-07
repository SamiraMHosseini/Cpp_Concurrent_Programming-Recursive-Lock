# Practice-Multithreading
​CPP_Multithreaded_Practice_RecursiveLock ​

A recursive mutex in C++ multithreaded programming is a type of mutual exclusion (mutex) that 
allows a thread to lock the same mutex multiple times without causing deadlock. Unlike a normal mutex, 
which only allows a single lock, a recursive mutex keeps track of the number of locks acquired by 
the same thread and only unlocks the mutex when the same number of unlocks have been performed. 
This is useful in situations where a thread may need to enter a critical section multiple times, for example,
when implementing a recursive algorithm.
A recursive mutex is similar to a normal mutex, 
but with one important difference: a thread can lock a recursive mutex multiple times, 
and it must unlock the mutex the same number of times to actually unlock it.
