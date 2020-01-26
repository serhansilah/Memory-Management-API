# Memory-Management-API

The part of the operating system that manages (part of) the memory hierarchy is called the memory manager. Its job is to efficiently manage memory: keep track of which parts of mem- ory are in use, allocate memory to processes when they need it, and deallocate it when they are done.
In general terms, there are two ways to keep track of memory usage: bitmaps and free lists. With a bitmap, memory is divided into allocation units as small as a few words and as large as several kilobytes. Corresponding to each allocation unit is a bit in the bitmap, which is 0 if the unit is free and 1 if it is occupied (or vice versa).
Another way of keeping track of memory is to maintain a linked list of allocated and free memory segments, where a segment either contains a process or is an empty hole between two processes.


We are going to use POSIX threads which will work on the shared data structures. 
We should use POSIX threads, semaphores, mutex or mutexes, linked list and queue data structures and a main memory array.

In general case, the memory is divided into fixed size of chunks. In this we are assuming one chunk is 1 Byte.

The memory array that will be used in this will be a char array with size M. Since each chunk is 1 Byte size, total memory will be M bytes size. If the memory address is free,
there should be X in the proper memory index. If it is allocated by a thread, the thread ID should be written in the proper memory index.

We need to maintain a linked list for free and allocated memory indexes. The purpose of the linked list is tracking the memory state. The linked list should be updated with each memory allocation or deallocation.

A linked list node should contain; ID, SIZE and INDEX variables.
A hole (free memory) or an allocated thread information could be represented by a linked list node.
For a thread; ID denotes the unique integer given to that thread, SIZE denotes the random integer created during the execution. INDEX denotes the starting memory index of the thread. For a hole; ID equals to -1, SIZE denotes the size of free memory, INDEX denotes the starting memory index of hole. The linked list should be formed by using the above node.

We need to maintain a queue for thread memory requests. The purpose of the queue is ordering the thread requests so that memory server can process them one by one.
A queue node should contain; ID and SIZE variables.
ID denotes the unique integer given to that thread, SIZE denotes the random integer created during the execution.

