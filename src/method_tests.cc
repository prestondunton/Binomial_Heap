#include "binomial_heap.h"
#include <iostream>
#include <cassert>

using namespace std;

void print_test_banner(const string &s){
	cout<< setfill('=') << "\n====================" << setw(35) << left << s << "\n\n";
	cout << setfill(' ') << right;
}

void test_node(){
	print_test_banner("Testing Node Class");

	Node n1;
	n1.key_ = 50;
	n1.degree_ = 39;
	cout << n1 << "\n";

	Node n2(60);
	n2.degree_ = 40;
	n2.parent_ = &n1;
	cout << n2 << "\n";

	Node n3(70);
	n3.degree_ = 41;
	n3.parent_ = &n1;
	n3.sibling_ = &n2;
	cout << n3 << "\n";

	Node n4(80);
	n4.degree_ = 42;
	n4.parent_ = &n1;
	n4.sibling_ = &n2;
	n4.child_ = &n3;
	cout << n4 << "\n";


	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Node Class");
}

void test_size(){
	print_test_banner("Testing Size");

	Binomial_Heap bh;
	assert(bh.size() == 0);
	bh.insert(1);
	assert(bh.size() == 1);
	for(int i = 0; i < 500; i++)
		bh.insert(i);
	assert(bh.size() == 501);
	for(int i = 0; i < 47; i++)
		bh.extract_min();
	assert(bh.size() == 454);

	Node *new_node = bh.insert(543);
	assert(bh.size() == 455);
	bh.delete_node(new_node);
	assert(bh.size() == 454);

	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Size");
}

void test_empty(){
	print_test_banner("Testing Empty");

	Binomial_Heap bh;
	assert(bh.empty());	
	bh.insert(42);
	assert(!(bh.empty()));
	bh.extract_min();
	assert(bh.empty());	

	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Empty");
}

void test_insert(){

	print_test_banner("Testing Insert");

	Binomial_Heap bh;

	for(int i = -100; i < 100; i += 10){
		bh.insert(i);
	}
	
	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Insert");
}

void test_minimum(){

	print_test_banner("Testing Minimum");

	Binomial_Heap bh;

	for(int i = 99; i >= 0; i--)
		bh.insert(i);	
	
	for(int i = 0; i < 100; i++){
		assert(bh.minimum() == 0);
	}

	for(int i = 0; i < 100; i++){
		assert(bh.minimum() == i);
		bh.extract_min();
	}

	try {
		bh.minimum();
	} catch (...){
		cout << "\tAll tests passed!\n";
		print_test_banner("Done Testing Minimum");
	}
}

void test_extract_min(){
	print_test_banner("Testing Extract Min");

	Binomial_Heap bh;

	for(int i = 99; i >= 0; i--)
		bh.insert(i);	
	
	for(int i = 0; i < 100; i++){
		assert(bh.extract_min() == i);
	}

	try {
		bh.minimum();
	} catch (...){
		cout << "\tAll tests passed!\n";
		print_test_banner("Done Testing Extract Min");
	}
}

void test_heap_union(){

	print_test_banner("Testing Heap Union");

	Binomial_Heap bh1;
	Binomial_Heap bh2;
	Binomial_Heap bh3;
	Binomial_Heap bh4;

	
	for(int i = 0; i < 100; i+=2)
		bh1.insert(i);

	for(int i = 1; i < 100; i+=2)
		bh2.insert(i);

	bh1.heap_union(bh2);

	for(int i = 0; i < 100; i++)
		assert(bh1.extract_min() == i);

	for(int i = 250; i >= 150; i--)
		bh1.insert(i);

	bh3.heap_union(bh1);

	for(int i = 150; i <= 250; i++)
		assert(bh3.extract_min() == i);

	for(int i = 250; i >= 150; i--)
		bh2.insert(i);

	bh2.heap_union(bh4);

	for(int i = 150; i <= 250; i++)
		assert(bh2.extract_min() == i);


	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Heap Union");
}

void test_decrease_key(){

	print_test_banner("Testing Decrease Key");

	Binomial_Heap bh;
	Node *max;	

	for(int i = 0; i < 256; i++){
		max = bh.insert(i);
	}

	bh.decrease_key(max,-3);
	assert(bh.extract_min() == -3);
	assert(max->key_ != 255);

	bh.decrease_key(max,-2);
	assert(bh.extract_min() == -2);
	assert(max->key_ != 254);

	bh.decrease_key(max,-1);
	assert(bh.extract_min() == -1);
	assert(max->key_ != 253);

	while(!bh.empty())
		bh.extract_min();

	try {
		bh.decrease_key(max,1000000);
	} catch(...) {
		cout << "\tAll tests passed!\n";
	}
	print_test_banner("Done Testing Decrease Key");

}

void test_delete_node(){

	print_test_banner("Testing Delete Node");

	Binomial_Heap bh;

	Node *five = nullptr;
	Node *six = nullptr;
	Node *seven = nullptr;

	Node *result;
	for(int i = 0; i < 10; i++){
		result = bh.insert(i);
		if(i == 5)
			five = result;
		if(i == 6)
			six = result;
		if(i == 7)
			seven = result;
	}

	assert(bh.size() == 10);

	bh.delete_node(five);
	bh.delete_node(six);
	bh.delete_node(seven);

	assert(bh.size() == 7);

	for(int i = 0; i < 10; i++){
		if(i == 5 || i == 6 || i == 7)
			continue;
		assert(bh.extract_min() == i);
	}

	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Delete Node");
}

void test_clear(){

	print_test_banner("Testing Clear");

	Binomial_Heap bh;
	
	for(int i = 0; i < 1000; i++)
		bh.insert(i);

	assert(bh.size() == 1000);
	assert(!bh.empty());
	
	bh.clear();
	
	assert(bh.size() == 0);
	assert(bh.empty());

	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Clear");
}

void test_copy_ctor(){

	print_test_banner("Testing Copy Constructor");

	Binomial_Heap bh1;

	for(int i = 0; i < 100; i++)
		bh1.insert(i);

	Binomial_Heap bh2(bh1);
	assert(bh1.size() == bh2.size());
	assert(bh1.head() != bh2.head());

	for(int i = 0; i < 100; i++)
		assert(bh2.extract_min() == i);

	for(int i = 0; i < 100; i++)
		assert(bh1.extract_min() == i);

	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Copy Constructor");
}

void test_assign_operator(){

	print_test_banner("Testing Assignment Operator");

	Binomial_Heap empty;
	Binomial_Heap tens;
	Binomial_Heap twenties_thirties;

	for(int i = 10; i < 20; i++)
		tens.insert(i);
	for(int i = 20; i < 40; i++)
		twenties_thirties.insert(i);


	Binomial_Heap test;

	test = tens;
	assert(test.size() == tens.size());
	assert(test.head() != tens.head());

	test = test;
	assert(!test.empty());

	test = empty;
	assert(test.empty()); 

	test = twenties_thirties;
	assert(test.size() == twenties_thirties.size());
	assert(test.head() != twenties_thirties.head());

	for(int i = 20; i < 40; i++)
		assert(test.extract_min() == i);

	assert(test.empty());
	assert(!twenties_thirties.empty());

	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Assignment Operator");
}

void test_post_print(){
	print_test_banner("Testing Post Print");

	vector<int> nums = {10,1,12,25,18,6,8,14,29,11,17,38,27};
	Binomial_Heap bh;

	for(auto n : nums)
		bh.insert(n);
	
	post_print(cout, bh);

	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Post Print");
}

void test_pre_print(){
	print_test_banner("Testing Pre Print");

	vector<int> nums = {10,1,12,25,18,6,8,14,29,11,17,38,27};
	Binomial_Heap bh;

	for(auto n : nums)
		bh.insert(n);
	
	pre_print(cout, bh);

	cout << "\tAll tests passed!\n";
	print_test_banner("Done Testing Pre Print");
}

int main(){

	test_node();

	test_size();
	test_empty();
	test_insert();
	test_minimum();
	test_extract_min();
	test_heap_union();
	test_decrease_key();
	test_delete_node();
	test_clear();
	test_copy_ctor();
	test_assign_operator();

	test_post_print();
	test_pre_print();

	cout << "\nDone running all tests!\n\n";

	return 0;	
}
