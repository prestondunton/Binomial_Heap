# Binomial_Heap
An implementation of the binomial heap data structure.

<img src="http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/404_a.gif" alt="Binomial Heap" width="50%" height="50%">

### Overview
Binomial heaps are a special type of heap which support the .heap_union() method in O(log(n)) time.  In fact, most methods of the binomial heap run in O(log(n)) time.  Binomial heaps are structured as a linked list of binomial trees, whose roots all have unique degrees.  Binomial trees are defined recursively and are structured so that a tree B<sub>k</sub> has a root of degree k and 2<sup>k</sup> nodes.  A binomial heap is a collection of these trees where each tree satisfies the heap property. This property and the fact that the root list of the heap contains at most log(n) roots is what allows most operations to run in log(n) time.  For more reading about the data structure, visit https://en.wikipedia.org/wiki/Binomial_heap.

### This Implementation
Binomial heaps in this project are implemented in C++ as `binomial_heap.cc` with a header file `binomial_heap.h`.  A CMakeLists.txt file is included so that the project can be compiled using `cmake`.  This implementation is for a minimum binomial heap of integers.  Memory is implemented by managing dynamic `Node` objects which encapsulate the integers stored.  The Binomial_Heap class offers a copy constructor, assignment operator, and destructor to better reflect the operators provided by STL containers.  Unlike STL containers, this implementation is not templated, meaning it can only store integers.  It also does not provide iterators.  These could be added with more time spent on the project.

### Testing and Time Analysis
There are two files used for testing: `method_tests.cc` and `time_tests.cc`.  The   `method_tests.cc` tests the functionality of the the methods offered by the `Binomial_Heap` class to ensure the class works.  The `time_tests.cc` is used to analyze how long the various operations take by recording how long a call takes in nanoseconds.  This data is then writen to `.csv` files.  The `.csv` files were opened using RStudio and analyzed using R.  Each folder in the `time_analysis` folder contains the `.csv`, `.R` and the output of the `.R` saved as a `.pdf`.  In the `.pdf`s you will find a thourough analysis of the time complexity for each method in the implementation.

### Achieved Time Complexities
Method | Big-O Bound
-------|------------
Copy Constructor | O(n)
Assignment Operator | O(n+m)
.size() | O(log(n))
.empty() | O(1)
.insert() | O(log(n))
.minimum() | O(log(n))
.extract_min() | O(log(n))
.heap_union() | O(log(n+m))
.decrease_key() | O(log(n))
.delete_node() | O(log(n))
.clear() | O(log(n))

For methods that involve two different heaps, `n` represents the number of elements in the first heap and `m` represents the number of elements in the second heap.
E.g. `heap_of_size_n = heap_of_size_m;` and `heap_of_size_n.heap_union(heap_of_size_m);`.
