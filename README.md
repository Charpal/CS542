o# CS542
Project for a class
For this assignment, you will write a C++ program to simulate a Level 1 write-back cache.  You do not need to write any part of this assignment in assembler language.  You may assume that the memory being simulated uses 32-bit words and byte addressing, just like the Intel x86 family.
Input
The input will be a series of parameters and test data within a file.  The input will be in character format.  The input data will comprise:
a.  Line size of the cache.
b.  Total size of the cache.
c.  Associativity of the cache.
d.  Total size of main memory.
e.  Address, type of access, and data for simulated memory accesses.
f.   Address of data to be displayed.
There are only one instance of items a through d.  Items e and f will repeat multiple times.  All input data will comprise a character code (A-F) and one data value (or three for item e).
For example,
E 4004 W 5657
Means Write the value 5657 to location 4004.  Also,
F 4004
Means that the contents of the cache and main memory for location 4004 should be displayed.
Processing
Read in the four primary variables (items a through d above).  Validate them with the following rules:
1.  All values must be greater than zero
2.  All values must be multiples of a power of 2.  Thus, 2, 4, 8, 16, 32, 64, and so forth are valid values; odd numbers such as 1, 13, or 111 are not valid, and even numbers which are not a multiple of a power of 2 are invalid, such as 6, 22, or 46.  Thus, 384 is valid (multiple of 2 to the seventh power, or 128), while 386 is not.  However, for this assignment, you only need to check that the values are even numbers.
3.  Line size (a) may not exceed ten percent of the cache size.
4.  Cache size may not exceed ten percent of the total size of main memory.
The program should issue an error message and end if any of these tests fail, or if any of parameters a through d are omitted.Once parameters a through d have been validated, initialize the simulated memory system.  Acquire memory for the cache and for the memory.  You also may find it useful to establish a separate array for an associative memory.  (These should all be separate variables.)  Set all memory to zeroes, minus 1, or some other identifiable value.  Then begin a processing loop.  
Read the input data and process all memory accesses.  For write accesses, store the value in the cache.  For read accesses, get the data from the cache if present, or from main memory if not, and move the data into the cache in that case.   If a write access references a cache line which already has data, copy that data from the cache to the simulated main memory before storing the incoming value into the simulated cache.For item f, display the address, value in the simulated cache for that address, and data in simulated main memory for that address.
Output
Your program should produce the following lines of output as appropriate:
Output Line 1:
Invalid value n for itemReplace item with the name (line size, cache size, et cetera) and n with the value from the file.
Output Line 2:
Item n too large Replace item with cache size or line size, and n with the value from the file.
Output Line 3:
Input address xxxxxxxx invalidReplace xxxxxxxx with the address field from the memory access line (input type E)
Output Line 4:
Address: xxxxxxxx memory:nnnnnnnn cache:mmmmmmmm
Replace xxxxxxxx with the address field from the memory data display field (input type F), nnnnnnnn with the simulated memory contents for that address, and mmmmmmmm with the simulated cache contents for that address.  If the cache line is not valid, display -1 for that value.
Sample Input File:
A 16
B 2048
C 2
D 32768
E 0 W 22222222
E 8 W 1234
E 32 W 1233
E 16 W 888
F 0 
E 4 W 33333333
F 8 
E 1028 W 3231
E 16388 W 5657
F 0F 4
F 8F 12
F 16
F 1024
F 1028
F 16384
F 16388
