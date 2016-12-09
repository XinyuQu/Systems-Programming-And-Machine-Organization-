README for CS 61 Problem Set 6
------------------------------
YOU MUST FILL OUT THIS FILE BEFORE SUBMITTING!
** DO NOT PUT YOUR NAME OR YOUR PARTNER'S NAME! **

RACE CONDITIONS
---------------
Write a SHORT paragraph here explaining your strategy for avoiding
race conditions. No more than 400 words please.

To avoid race conditions in this pset, I have provided mutual exclusion in multiple critical sections. Critical sections are defined as chunks of code that access a shared resource that should never be concurrently accessed by more than a single thread. Mutual exclusion ensures that at the same time, no two threads are in the same critical section.
Firstly, the critical sections in this pset are when a thread accesses the array, traverses it or adds a connection to it. This is to ensure that two threads do not try to reuse the same connection at the same time by accessing the same element in the array. Also, it ensures that two threads when filling up the array with a new connection do not add the new connection to the same element, resulting in only one being added. Hence, manipulating the array is only done by a single thread at one point in time.
The same lock is used around the code line of sleep (which is another critical section) while dealing with Phase 4 (overloading). This ensures that while the thread’s execution is suspended, connections can also not be reused and the array cannot be traversed. This ensures that the server does not get overloaded. 
Lastly, another critical section is around the call to http_connect so that only one thread attempts to open a new connection to the server at a time. Technically, the critical section should cover the call to http_connect as well as the sending of the request but this is not possible in this pset because of the way the server is written (the assignment instructions say that it is impossible to avoid all client–server race conditions).
Locking is important as when I have multiple threads, any order cannot be guaranteed. Some sections of code should not be manipulated simultaneously as explained above which is why I need to lock. 

OTHER COLLABORATORS AND CITATIONS (if any):

section notes

KNOWN BUGS (if any):



NOTES FOR THE GRADER (if any):



EXTRA CREDIT ATTEMPTED (if any):
