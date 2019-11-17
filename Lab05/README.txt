Kyle Jeffrey

Selection Sort:
time: 76.264 ms

Insertion Sort:
time: 49.804

The insertion sort method was definitevely faster than selection sort. It's difficult to describe exactly why this is the case but I assume it has to do with compartamentalizing the problem into sections and working with smaller data samples. 

Summary: 
The lab began with creating a double linked list frame work for creating arrays that can expand indefinitely. The linked lists were then used to impliment sorting alogorithms: Selection sort and Insertion sort. These both took in strings and sorted alphabetically. 

Approach: 
I began this lab by taking time to watch some instructional videos on linked lists to get a feel for their importance. Then I began creating the functions for the linked lists, naturally beginning with LinkedListNew() and LinkedListPrint() for debugging early on. Once I was sure the linked lists had good implimentation, I moved onto the sorting algorithms. The pseudo code was very helpful in the implimentation of these, but I had to walk step by step through the Insertion Sort especially to really get a feel for how the algorithm worked. 

Conclusion: 
In total, the lab probably took me 10 hours or so to get down correctly. The largest chunks of time I spent were on small edge case bugs that invariably were null pointer errors. The general architecture for the sorting algorithms flowed without resistance but, getting the last iteration of the algorithms to not point at a null address was the bane of my errors. 