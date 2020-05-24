#include "binomial_heap.h"

using namespace std;

Node::Node() : Node::Node(0){}

Node::Node(const int k) : parent_(nullptr), key_(k), degree_(0), sibling_(nullptr), child_(nullptr){}

ostream &operator<<(ostream &o, const Node &node){
	o << "Node [" << &node << "]:" 
	<< " parent(" << setw(14) << node.parent_ << ") " 
	<< " key(" << node.key_ << ") " 
	<< " degree(" << node.degree_ << ") " 
	<< " sibling(" << setw(14) << node.sibling_ << ") " 
	<< " child(" << setw(14) << node.child_ << ")"; 
	return o;
}

////////////////////////////////////////////////////////////////////////////


Binomial_Heap::Binomial_Heap(const Binomial_Heap &bh){
	head_ = copy_tree(bh.head(), nullptr);
}
Binomial_Heap::~Binomial_Heap(){
	//cout << "~Binomial_Heap() was called!\n";
	if(delete_on_destroy_)
		delete_tree(head_);
}

Binomial_Heap &Binomial_Heap::operator=(const Binomial_Heap &bh){
	if(&bh != this){ // to handle self assignment correctly
		delete_tree(head_);
		head_ = copy_tree(bh.head(), nullptr);
	}
	return *this;
}


size_t Binomial_Heap::size() const {
	size_t size = 0;
	if(head_ != nullptr){
	
		Node *current = head_;
		while(current != nullptr){
			size += pow(2,current->degree_);	
			current = current->sibling_;
		}
	}

	return size;
}

bool Binomial_Heap::empty() const {
	return head_ == nullptr;
}


Node *Binomial_Heap::insert(int x){
	//cout << "insert() was called!\n";
	Binomial_Heap temp;

	Node *new_node = new Node;
	new_node->key_ = x;

	temp.head(new_node);
	temp.delete_on_destroy_ = false;
	this->heap_union(temp);

	return new_node;
}

int Binomial_Heap::minimum() const {
	//cout << "minimum() was called!\n";
	if(empty())
		throw range_error("Tried to call .minimum() on an empty Binomial_Heap");
	Node *pre_min_node = _minimum();
	if(pre_min_node == nullptr){
		//cout << "returning from minimum() with " << head_->key_ << "\n";
		return head_->key_;
	}

	//cout << "returning from minimum() with " << pre_min_node->sibling_->key_ << "\n";
	return pre_min_node->sibling_->key_;	
}
int Binomial_Heap::extract_min(){
	//cout << "extract_min() was called!\n";
	if(empty())
		throw range_error("Tried to call .extract_min() on an empty Binomial_Heap");

	Node *pre_min_node = _minimum();
	Node *min_node;
	if(pre_min_node == nullptr){
		min_node = head_;
		head_ = min_node->sibling_; // remove min node from list
	} else {
		min_node = pre_min_node->sibling_;
		pre_min_node->sibling_ = min_node->sibling_; // remove min node from list
	}
	
	if(min_node->degree_ == 0){ // if min_node has no children, we don't have to worry about the children of min_node because there aren't any
		//cout << "returning from extract_min() with " << min_node->key_ << " because heap is now empty or min_node->degree_ == 0\n";
		//cout << "empty(): " << empty() << "\n";
		return min_node->key_;
	}
	
	Node *new_head = min_node->child_;
	Node *current = min_node->child_->sibling_;
	Node *next;

	new_head->sibling_ = nullptr;	
	new_head->parent_ = nullptr;	

	while(current != nullptr){ // reverse the linked list of min_node's children and clear their parent pointers
		next = current->sibling_;	
		current->sibling_ = new_head;
		current->parent_ = nullptr;
		new_head = current;
		current = next;
	}


	Binomial_Heap temp; // make a new heap from the children of min_node
	temp.head(new_head);
	temp.delete_on_destroy_ = false;

	//cout << "temp heap:\n" << temp << "\n";

	this->heap_union(temp);	// merge the children of min_node back into this heap

	int min = min_node->key_;
	delete min_node;
	//cout << "returning from extract_min() with " << min << "\n";
	return min;
	
}
void Binomial_Heap::heap_union(Binomial_Heap &bh){ 
	// takes bh and puts its nodes into this's heap
	// it then makes bh's head a nullptr so it can be used again
	// does not preserve either of the two heaps
	//cout << "heap_union() was called!\n";

	if(bh.empty()){
		//cout << "uniting empty heap onto this!\n";
		return;
	}
	if(this->empty()) {
		//cout << "uniting onto an empty heap!\n";
		this->head_ = bh.head();
		bh.head(nullptr);
		return;
	}

	//cout << "uniting two non empty heaps\n";
	this->binomial_heap_merge(bh);

	Node *prev = nullptr;
	Node *current = this->head_;
	Node *next = this->head_->sibling_;

	while(next != nullptr){
		if(current->degree_ != next->degree_ ||
		  (next->sibling_ != nullptr && 
		   next->sibling_->degree_ == current->degree_)){
			prev = current; //Case 1 and 2
			current = next;	
		} else if(current->key_ <= next->key_){
			current->sibling_ = next->sibling_; //Case 3
			binomial_link(next,current);
		} else {
			if(prev == nullptr){ //Case 4
				this->head_ = next;
			} else {
				prev->sibling_ = next;
			}
			binomial_link(current,next);
			current = next;
		}
		
		next = current->sibling_;
	}
	bh.head(nullptr);
}
void Binomial_Heap::decrease_key(Node *node, const int k){
	if(k > node->key_)
		throw invalid_argument(".decrease_key() cannot decrease key from " + to_string(node->key_) + " to " + to_string(k));
	node->key_ = k;
	bubble_up(node);
}
void Binomial_Heap::delete_node(Node *node){
	decrease_key(node,numeric_limits<int>::min());
	extract_min();
}

void Binomial_Heap::clear(){
	delete_tree(head_);
	head_ = nullptr;
}


Node *Binomial_Heap::head() const {
	return head_;
}

void Binomial_Heap::head(Node *h){
	head_ = h;
}


Node *Binomial_Heap::_minimum() const {
	// assumes heap is not empty, returns node whose sibling is the minimum
	// useful for extracting the min node
	

	//cout << "_minimum() was called!\n";

	Node *pre_min_node = nullptr;
	Node *previous = nullptr;
	Node *current = head_;
	int min = head_->key_;
	while(current != nullptr){
		if(current->key_ < min){
			min = current->key_;
			pre_min_node = previous;
		}
		previous = current;
		current = current->sibling_;
	}

	//cout << "returning from _minimum() with " << pre_min_node << "\n";
	return pre_min_node;	
}

void Binomial_Heap::binomial_link(Node *y,Node *z) {
	y->parent_ = z;
	y->sibling_ = z->child_;
	z->child_ = y;
	z->degree_ += 1;	
	return;
}

void Binomial_Heap::binomial_heap_merge(Binomial_Heap &bh){
	//cout << "merge() was called!\n";
	// takes two non emptry heaps and merges their root lists

	Node *current1 = this->head_;	
	Node *current2 = bh.head();	

	Node *dummy = new Node;
	Node *result_tail = dummy;

	while(current1 != nullptr || current2 != nullptr){
		if(current2 == nullptr){
			result_tail->sibling_ = current1;
			result_tail = current1;
			current1 = current1->sibling_;
		} else if(current1 == nullptr){
			result_tail->sibling_ = current2;
			result_tail = current2;
			current2 = current2->sibling_;
		} else {
			if(current1->degree_ <= current2->degree_){
				result_tail->sibling_ = current1;
				result_tail = current1;
				current1 = current1->sibling_;
			} else {
				result_tail->sibling_ = current2;
				result_tail = current2;
				current2 = current2->sibling_;
			}		
		}
	}

	this->head_ = dummy->sibling_;
	delete dummy;

	return;
}

void Binomial_Heap::bubble_up(Node *node){

	//cout << "\tbubbling up\n\t" << *node << "\n";

	if(node->parent_ == nullptr)
		return;

	Node *parent = node->parent_;
	if(node->key_ < parent->key_){
		swap(node,parent);
		bubble_up(parent);
	}
}

void Binomial_Heap::swap(Node *a, Node *b){
	//where b is the parent of a
	int temp = a->key_;
	a->key_ = b->key_;
	b->key_ = temp;
}


void Binomial_Heap::delete_tree(Node *root){
	if(root == nullptr)
		return;
	delete_tree(root->sibling_);
	delete_tree(root->child_);
	delete root;
}

Node *Binomial_Heap::copy_tree(Node *root, Node *copy_parent){
	if(root == nullptr)
		return nullptr;
	Node *copy = new Node;

	copy->key_ = root->key_;
	copy->degree_ = root->degree_;
	copy->parent_ = copy_parent;
	copy->sibling_ = copy_tree(root->sibling_, copy_parent);
	copy->child_ = copy_tree(root->child_, copy);

	return copy;
}

ostream &post_print(ostream &o, const Binomial_Heap &bh){
	return post_print_tree(o,bh.head());
}

ostream &post_print_tree(ostream &o, const Node *root, int indents){
	// TO DO
	if(root == nullptr)
		return o;

	//for(int i = 0; i < indents; i++)
		//o << "\t";
	
	post_print_tree(o, root->child_, indents+1);
	o << *root << "\n";
	post_print_tree(o, root->sibling_,indents);
	return o;	
}

ostream &pre_print(ostream &o, const Binomial_Heap &bh){
	return pre_print_tree(o,bh.head());
}

ostream &pre_print_tree(ostream &o, const Node *root, int indents){
	if(root == nullptr)
		return o;

//	for(int i = 0; i < indents; i++)
//		o << "\t";

	o << *root << "\n";
	pre_print_tree(o, root->child_, indents + 1);
	pre_print_tree(o, root->sibling_, indents);

	return o;
}

ostream &operator<<(ostream &o, const Binomial_Heap &bh){
	o << "Heap Size: " << bh.size() << "\n";
	o << "Heap Head: " << bh.head() << "\n\n";
	pre_print(o, bh);
	return o;
}
