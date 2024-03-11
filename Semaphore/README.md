MUTEX v/s SEMAPHORES 

-> Sempahore also works like a lock but instead of limiting the number of processes to 1 on a shared resoruce, it can let multiple processes manage a shared resource/resources. 

-> In practice, consider two contributors to a shared resource(eg buffer, linked list).

-> One type of contributor to the shared rescource is a producer and the other contributor is a consumer. 

-> The producer adds values to the shared buffer until the counting semaphore value allows it to.
   (Semaphore Increases)
   
   !!!(Counting Semaphore: Represents number of available slots in the shared buffer.)
   
-> The consumer pops values from a shared resource until the counting semaphore value allows it to.			
   (Semaphore Decreases)
    
------------------------MUTEX v/s SEMAPHORE------------------------

-> A process holding a mutex claims ownership of a resource and doesn't let other processes clain that resource until the Mutex has been given up. 

-> Semaphores are used to signal to other processes that a shared resource is ready to be used. 


-------------------------------------------------------------------

- Applications of Binary Semaphores:

Binary semaphores, with their simple two-state nature (0 or 1), can be used for various synchronization tasks in concurrent programming. Here are some common examples of how binary semaphores can be used:

- Mutual Exclusion:

Binary semaphores are often used to provide mutual exclusion, ensuring that only one thread at a time can access a critical section of code or a shared resource.
Example: Protecting a shared data structure, such as a linked list or a buffer, to prevent simultaneous access by multiple threads. Each thread must acquire the semaphore before accessing the data structure and release it afterward.

- Producer-Consumer Problem:

In a producer-consumer scenario, binary semaphores can be used to synchronize the interaction between the producer and consumer threads.
Example: Using a binary semaphore to control access to a shared buffer. The producer thread increments the semaphore count when it adds an item to the buffer, and the consumer thread decrements the count when it removes an item. This ensures that the producer waits if the buffer is full and that the consumer waits if the buffer is empty.

- Resource Allocation:

Binary semaphores can be used to manage access to a finite pool of resources, such as memory blocks or hardware peripherals.
Example: Using a binary semaphore to represent the availability of a resource. When a thread needs the resource, it attempts to acquire the semaphore. If the semaphore is available (1), the thread acquires the resource and decrements the semaphore count. If the semaphore is not available (0), the thread waits until the resource becomes available.

- Task Synchronization:

Binary semaphores can be used to coordinate the execution of multiple tasks or threads, ensuring that certain tasks are executed in a specific order or at specific times.
Example: Implementing a simple task scheduler where each task is associated with a binary semaphore. The scheduler releases the semaphore for a task when it is ready to execute, and the task waits on the semaphore until it is released.

- Interrupt Handling:

Binary semaphores can be used to synchronize between interrupt service routines (ISRs) and the main application code.
Example: Using a binary semaphore to signal the occurrence of an event in an ISR. The ISR sets the semaphore to indicate that the event has occurred, and the main application code waits on the semaphore until it is signaled.
