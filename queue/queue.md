-> using global variables to control one task from another is not a safe approach. 

-> queue is used to ensure that data that is written by tasks is written correctly. 

-> queue has global scope so that any task can access it and write it's own data to it. 

-> another task asynchronously reads data from the queue

-> A race condition is a situation that occurs in concurrent or multi-threaded programs when the outcome of the program depends on the timing or sequence of execution of multiple threads or processes. 

-> In other words, the behavior of the program becomes unpredictable because it depends on the relative timing of events, which can vary each time the program is executed.

-> Thread A reads the value of the shared variable.

   Thread B also reads the value of the shared variable.

   Thread A modifies the value of the shared variable based on its read value and stores it back.
   
   Thread B modifies the value of the shared variable based on its read value and stores it back.

   The final value of the shared variable depends on the order in which Thread A and Thread B execute their operations. 
  
   If Thread A's modification is overwritten by Thread B's modification, the final value will be different from what Thread A intended.
