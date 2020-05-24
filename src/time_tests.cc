#include "binomial_heap.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

void write_csv(const string &filename, const vector<int> &n, const vector<int> &t, const vector<long> &total_t){
	if(n.size() != t.size())
		throw invalid_argument("vectors n and t are of different sizes");
	if(t.size() != total_t.size())
		throw invalid_argument("vectors t and total_t are of different sizes");


	ofstream new_csv(filename);	

	new_csv << "N,T,Total_T\n";
	
	for(size_t i = 0; i < n.size(); i++)
		new_csv << n[i] << "," << t[i] << "," << total_t[i] << '\n';

	new_csv.close();
}

void write_csv(const string &filename, const vector<int> &n, const vector<int> &m, const vector<int> &t, const vector<long> &total_t){
	if(n.size() != m.size())
		throw invalid_argument("vectors n and m are of different sizes");
	if(m.size() != t.size())
		throw invalid_argument("vectors m and t are of different sizes");
	if(t.size() != total_t.size())
		throw invalid_argument("vectors t and total_t are of different sizes");


	ofstream new_csv(filename);	

	new_csv << "N,M,T,Total_T\n";
	
	for(size_t i = 0; i < n.size(); i++)
		new_csv << n[i] << "," << m[i] << "," << t[i] << "," << total_t[i] << '\n';

	new_csv.close();
}

void time_copy_ctor(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bh;

	for(int i = 0; i < 1e5; i++){
		auto start = steady_clock::now();
		Binomial_Heap copy(bh);
		auto stop = steady_clock::now();
		auto ns = duration_cast<nanoseconds>(stop-start);
		total += ns.count();

		if(i % 100 == 0){
			n.push_back(i);
			t.push_back(ns.count());
			total_t.push_back(total);
		}
		
		bh.insert(gen());
		
	}

	write_csv("copy_ctor_binomial.csv",n,t,total_t);
}

void time_assignment_operator(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> m;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bhn;

	for(int i = 0; i < 1e5; i+=100){
	
		Binomial_Heap bhm;

		for(int j = 0; j < 1e5; j+=100){
			Binomial_Heap copy(bhn);
			auto start = steady_clock::now();
			copy = bhm; // bhn = bhm
			auto stop = steady_clock::now();
			auto ns = duration_cast<nanoseconds>(stop-start);
			total += ns.count();

			n.push_back(i);
			m.push_back(j);
			t.push_back(ns.count());
			total_t.push_back(total);
			cout << "assignment " << i << " " << j << '\n';

			for(int k = 0; k < 100; k++)
				bhm.insert(gen());
			
		}

		for(int k = 0; k < 100; k++)
			bhn.insert(gen());
	}

	write_csv("assignment_operator_binomial.csv",n,m,t,total_t);
}

void time_size(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bh;

	for(int i = 0; i < 1e7; i++){
		auto start = steady_clock::now();
		bh.size();		
		auto stop = steady_clock::now();
		auto ns = duration_cast<nanoseconds>(stop-start);
		total += ns.count();

		if(i % 100 == 0){
			n.push_back(i);
			t.push_back(ns.count());
			total_t.push_back(total);
		}
		
		bh.insert(gen());
		
	}

	write_csv("size_binomial.csv",n,t,total_t);
}

void time_empty(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bh;

	for(int i = 0; i < 1e7; i++){
		auto start = steady_clock::now();
		bh.empty();		
		auto stop = steady_clock::now();
		auto ns = duration_cast<nanoseconds>(stop-start);
		total += ns.count();

		if(i % 100 == 0){
			n.push_back(i);
			t.push_back(ns.count());
			total_t.push_back(total);
		}
		
		bh.insert(gen());
		
	}

	write_csv("empty_binomial.csv",n,t,total_t);

}

void time_insert(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bh;

	for(int i = 0; i < 1e7; i++){
		auto start = steady_clock::now();
		bh.insert(gen());		
		auto stop = steady_clock::now();
		auto ns = duration_cast<nanoseconds>(stop-start);
		total += ns.count();
		if(i % 100 == 0){
			n.push_back(i);
			t.push_back(ns.count());
			total_t.push_back(total);
		}
	}

	write_csv("insert_binomial.csv",n,t,total_t);
}

void time_minimum(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bh;

	bh.insert(gen());

	for(int i = 1; i < 1e7; i++){
		auto start = steady_clock::now();
		bh.minimum();
		auto stop = steady_clock::now();
		auto ns = duration_cast<nanoseconds>(stop-start);
		total += ns.count();
		if(i % 100 == 0){
			n.push_back(i);
			t.push_back(ns.count());
			total_t.push_back(total);
		}
		bh.insert(gen());		
	}

	write_csv("minimum_binomial.csv",n,t,total_t);
}

void time_extract_min(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bh;

	bh.insert(gen());

	for(int i = 1; i < 1e7; i++){
		auto start = steady_clock::now();
		bh.extract_min();
		auto stop = steady_clock::now();
		auto ns = duration_cast<nanoseconds>(stop-start);
		total += ns.count();
		if(i % 100 == 0){
			n.push_back(i);
			t.push_back(ns.count());
			total_t.push_back(total);
		}
		bh.insert(gen());		
		bh.insert(gen());		
	}

	write_csv("extract_min_binomial.csv",n,t,total_t);
}

void time_heap_union(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> m;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bhn;

	for(int i = 0; i < 1e5; i+=100){
	
		Binomial_Heap bhm;

		for(int j = 0; j < 1e5; j+=100){
			Binomial_Heap copyn(bhn);
			Binomial_Heap copym(bhm);
			auto start = steady_clock::now();
			copyn.heap_union(copym);
			auto stop = steady_clock::now();
			auto ns = duration_cast<nanoseconds>(stop-start);
			total += ns.count();

			n.push_back(i);
			m.push_back(j);
			t.push_back(ns.count());
			total_t.push_back(total);
			cout << "union " << i << " " << j << '\n';
	
			for(int k = 0; k < 100; k++)		
				bhm.insert(gen());
			
		}

		for(int k = 0; k < 100; k++)		
			bhn.insert(gen());
	}

	write_csv("heap_union_binomial.csv",n,m,t,total_t);
}

void time_decrease_key(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bh;

	for(int i = 1; i < 1e7; i++){
		Node *new_node = bh.insert(gen());
		int random_less = gen();
		while(random_less >= new_node->key_)
			random_less = gen();
		auto start = steady_clock::now();
		bh.decrease_key(new_node, random_less);
		auto stop = steady_clock::now();
		auto ns = duration_cast<nanoseconds>(stop-start);
		total += ns.count();

		if(i % 100 == 0){
			n.push_back(i);
			t.push_back(ns.count());
			total_t.push_back(total);
		}
		
		
	}

	write_csv("decrease_key_binomial.csv",n,t,total_t);
}

void time_delete_node(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bh;

	for(int i = 1; i < 1e7; i++){
		Node *new_node = bh.insert(gen());
		auto start = steady_clock::now();
		bh.delete_node(new_node);
		auto stop = steady_clock::now();
		auto ns = duration_cast<nanoseconds>(stop-start);
		total += ns.count();

		if(i % 100 == 0){
			n.push_back(i);
			t.push_back(ns.count());
			total_t.push_back(total);
		}

		bh.insert(gen());
		
	}

	write_csv("delete_node_binomial.csv",n,t,total_t);
}

void time_clear(){

	using namespace std::chrono;

	vector<int> n;
	vector<int> t;
	vector<long> total_t;
	minstd_rand gen;
	long total = 0;

	Binomial_Heap bh;

	for(int i = 0; i < 1e5; i++){
		Binomial_Heap copy(bh);
		auto start = steady_clock::now();
		copy.clear();		
		auto stop = steady_clock::now();
		auto ns = duration_cast<nanoseconds>(stop-start);
		total += ns.count();

		if(i % 100 == 0){
			n.push_back(i);
			t.push_back(ns.count());
			total_t.push_back(total);
		}
		
		bh.insert(gen());
		
	}

	write_csv("clear_binomial.csv",n,t,total_t);
}

int main(){

	time_copy_ctor();
	time_assignment_operator();
	time_size();	
	time_empty();
	time_insert();
	time_minimum();
	time_extract_min();
	time_heap_union();
	time_decrease_key();
	time_delete_node();
	time_clear();

	return 0;
}
