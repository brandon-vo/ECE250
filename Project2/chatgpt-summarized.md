This project involves implementing a hash table data structure in C++ to simulate virtual memory. 
Virtual memory is a system where a process appears to have its own memory space, even though it is 
sharing memory with other processes. The hash table is used to map each process's virtual pointers 
to their physical memory addresses.

There are two methods to resolve collisions in the hash table: (1) open addressing using double 
hashing, and (2) separate chaining with keys ordered by key. The hash functions provided are 
(1) a primary hash function that maps keys to a position in the table, and (2) a secondary hash 
function that resolves collisions in the case of open addressing.

Memory is represented by an array of integers and divided into pages of size P. The size of the 
hash table is N/P, where N is the size of the memory array and P is the size of each page. The 
virtual memory addresses begin at 0 and end at P-1. The project requires creating a class that 
represents a process, containing the process ID (PID) and the start address of its physical memory 
page. The PID is used as the hash key to store the process object in the hash table. When all 
blocks in the hash table are allocated, it is considered full.
