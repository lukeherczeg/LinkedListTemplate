#include <iostream>
#include <fstream>
using namespace std;

template<class T>
class Node {
public:
	T data;
	Node<T> * next;
};

template<class T>
class Iterator{
private:
	Node<T>* startNode;
	Node<T>* currentNode;
public:
	Iterator(Node<T> * startNode);
	bool end();
	void begin();
	Node<T> * current();
	void next();
};

template <class T>
class LinkedList{
private:
	Node<T> * head;
	Node<T> * tail;
public:
	void quickAppend(T value);
	void add(int index, T value);
	void remove(int index);
	T get(int index);
	void print();
	Iterator<T> * makeIterator();
};


template <class T> Iterator<T>::Iterator(Node <T> * startNode){ // @suppress("Class members should be properly initialized")
	this->startNode = startNode;
}

template <class T> bool Iterator<T>::end(){
	return this->currentNode == NULL;
}

template <class T> void Iterator<T>::begin(){
	this->currentNode = startNode;
}

template <class T> void Iterator<T>::next(){
	this->currentNode = this->currentNode->next;
}

template <class T> Node<T> * Iterator<T>::current(){
	return this->currentNode;
}

template <class T> int findAmountOfFragments(T valueSearchingFor, Iterator<T> * it){
	int count = 0;
	it->begin();
	while(!it->end()){
		if(it->current()->data == valueSearchingFor){
			count++;
			getToEndOfProgram(valueSearchingFor, it);
		}
		else {
			it->next();
		}
	}
	return count;
}


template <class T> Node<T> * findStartofLongestCSS(T valueSearchingFor, Iterator<T> * it){
	int max = 0;
	Node<T> * maxPointer = NULL;
	it->begin();
	while(!it->end()){
		if(it->current()->data == valueSearchingFor){
			Node<T> * possibleMax = it->current();
			int count = findContiguousSize(valueSearchingFor, it);
			if(count > max){
				max = count;
				maxPointer = possibleMax;
			}
		}
		else {
		it->next();
		}
	}
	std::cout << max << std::endl;
	return maxPointer;
}

template <class T> Node<T> * findStartOfLongestCSS(T valueSearchingFor, int minSize, Iterator<T> * it){
	int max = 0;
	Node<T> * maxPointer = NULL;
	it->begin();
	while(!it->end()){
		if(it->current()->data == valueSearchingFor){
			Node<T> * possibleMax = it->current();
			int count = findContiguousSize(valueSearchingFor, it);
			if(count > max && count >= minSize){
				max = count;
				maxPointer = possibleMax;
			}
		}
		else {
			it->next();
		}
	}
	std::cout << max << std::endl;
	return maxPointer;
}

template <class T> int findContiguousSize(T valueSearchingFor, Iterator<T> * it){
	int count = 0;
	while(!(it->end()) && it->current()->data == valueSearchingFor){
		count++;
		it->next();
	}
	return count;
}

template <class T> void getToEndOFProgram(T valueSearchingFor, Iterator<T> * it){
	while(!(it->end()) && it->current()->data == valueSearchingFor){
		it->next();
	}
}

template <class T> Iterator<T> * LinkedList<T>::makeIterator(){
	return new Iterator<T>(head);
}

template <class T> void LinkedList<T>::quickAppend(T value){
	if(head==NULL){
		head = new Node<T>();
		head->data = value;
		tail = head;
		return;
	}
	tail->next = new Node<T>();
	tail->next->data = value;
	tail = tail->next;
}

template <class T> void LinkedList<T>::add(int index,T value){
	if(index == 0){
		Node <T> * newNode = new Node<T>();
		newNode->data = value;
		newNode->next = head;
		head = newNode;
		return;
	}
	Node <T> * current = head;
	for(int i = 0; i < index - 1; ++i)
		current = current->next;
	Node <T> * newNode = new Node<T>();
	newNode->data = value;
	newNode->next = current->next;
	current->next = newNode;
	if(current == tail){
		tail = newNode;
	}
}

template <class T> void LinkedList<T>::remove(int index){
	if(index == 0){
		Node <T> * temp = head;
		head = head->next;
		delete temp;
		temp = NULL;
		return;
	}
	Node <T> * current = head;
	for(int i = 0; i < index - 1; ++i)
		current = current->next;
	Node <T> * temp = current->next;
	current->next = temp->next;
	if(temp == tail){
		tail = current;
	}
	current->next = current->next->next;
	delete temp;
	temp = NULL;
}

template <class T> void LinkedList<T>::print(){
	Node <T> * temp = head;
	while(temp != NULL){
		cout << temp->data << " -> ";
		temp = temp->next;
	}
	cout << "NULL\n";
}

int main() {
	LinkedList <int> * linkedList = new LinkedList<int>();
	linkedList->quickAppend(1);
	linkedList->quickAppend(1);
	linkedList->quickAppend(1);
	linkedList->quickAppend(2);
	linkedList->quickAppend(2);
	linkedList->quickAppend(3);
	linkedList->quickAppend(3);
	linkedList->quickAppend(1);
	linkedList->quickAppend(1);
	linkedList->quickAppend(3);
	linkedList->quickAppend(3);
	linkedList->quickAppend(3);
	linkedList->remove(3);
	std::cout << findContiguousSize(1, linkedList->makeIterator());
	findStartOfLongestCSS(1, 2, linkedList->makeIterator());
	linkedList->print();

	return 0;
}






