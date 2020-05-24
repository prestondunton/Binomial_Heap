#ifndef BINOMIAL_HEAP_INCLUDED
#define BINOMIAL_HEAP_INCLUDED
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <limits> // for delete_node
#include <vector>
#include <cmath> //for pow for calculating size()

/*
 * TO DO
 * RAII
 * 	union should take a bh by value so that its nodes aren't deleted for temp
 * finish methods and test functionality
 * make class templated
 * make binary heap (maybe set?)
 * time test 
 */

class Node {
    public:

	Node();
	Node(const int);
	~Node() = default;

	Node *parent_;
	int key_;
	int degree_;
	Node *sibling_;
	Node *child_;
};

std::ostream &operator<<(std::ostream &, const Node &);

class Binomial_Heap {
    public:
	Binomial_Heap() = default; //Make-Heap()
	Binomial_Heap(const Binomial_Heap &);
	~Binomial_Heap();
	Binomial_Heap &operator=(const Binomial_Heap &);

	size_t size() const;
	bool empty() const;

	Node *insert(int);
	int minimum() const ;
	int extract_min();
	void heap_union(Binomial_Heap &);
	void decrease_key(Node *, const int k);
	void delete_node(Node *);
	
	void clear();

	Node *head() const;
	void head(Node *);

    private:

	Node *_minimum() const ;
	void binomial_link(Node *,Node *);
	void binomial_heap_merge(Binomial_Heap &);
	void bubble_up(Node *);
	void swap(Node *, Node *);
	void delete_tree(Node *);
	Node *copy_tree(Node *, Node *);

	Node *head_ = nullptr;
	bool delete_on_destroy_ = true;
};

std::ostream &post_print(std::ostream &, const Binomial_Heap &);
std::ostream &post_print_tree(std::ostream &, const Node *, int = 0);

std::ostream &pre_print(std::ostream &, const Binomial_Heap &);
std::ostream &pre_print_tree(std::ostream &, const Node *, int = 0);

std::ostream &operator<<(std::ostream &, const Binomial_Heap &);


#endif /*BINOMIAL_HEAP_DEFINED */
