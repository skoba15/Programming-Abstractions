/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

/* constructor, initializes the array size, sets allocated memory size to zero */
HeapPriorityQueue::HeapPriorityQueue() {
	arraysize=INITIAL_SIZE;
	allocsize=0;
	arr=new string[arraysize];
}

/* destructor which deletes the array */
HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] arr;
}

/* returns the size of the queue */
int HeapPriorityQueue::size() {
	return allocsize;
}

/* returns true if the queue is empty*/
bool HeapPriorityQueue::isEmpty() {
	return allocsize==0;
}

/* adds new value to the queue */
void HeapPriorityQueue::enqueue(string value) {
	if(allocsize==arraysize){
		allocnewmemory();
		arr[allocsize]=value;
	}
	else{
		arr[allocsize]=value;
	}
	if(allocsize>=1){
		Bubbleup();
	}
	++allocsize;
}


/* returns the minimal element of the queue */
string HeapPriorityQueue::peek() {
	if(allocsize==0){
		error("there is no element in priority queue");
	}
	else{
		return arr[0];
	}
}

/* returns the minimal element from the queue and removes it*/
string HeapPriorityQueue::dequeueMin() {
	string s;
	if(allocsize==0){
		error("there is no element in priorirty queue");
	}
	else{
		s=arr[0];
		bubbleDown();
		return s;
	}
	return "";
}

/* allocates new memory for the array */
void HeapPriorityQueue::allocnewmemory(){
	arraysize=arraysize*GROWSIZE;
	string * p=new string[arraysize];
	for(int i=0; i<allocsize; ++i){
		p[i]=arr[i];
	}
	delete[] arr;
	arr=p;
}

/* finds the adequate place for the newly added element */
void HeapPriorityQueue::Bubbleup(){
	int index=allocsize;
	for(int i=allocsize; i>=0; i=(i-1)/2){
		if(arr[index]<arr[i]){
			string tmp=arr[i];
			arr[i]=arr[index];
			arr[index]=tmp;
			index=i;
		}
		if(i==0)break;
	}
}

/* finds the appropriate place for the top element */
void HeapPriorityQueue::bubbleDown(){
	string tmp=arr[allocsize-1];
	arr[allocsize-1]=arr[0];
	arr[0]=tmp;
	arr[allocsize-1]="";
	--allocsize;
	int i;
	for(i=0; i<allocsize;){
		if(2*i+2<allocsize){
			int index;
			string name;
			string node1=arr[2*i+1];
			string node2=arr[2*i+2];
			if(node1<node2){
				index=2*i+1;
				name=node1;
			}
			else {
				index=2*i+2;
				name=node2;
			}
			if(arr[i]>name){
				string tmp=arr[i];
				arr[i]=arr[index];
				arr[index]=tmp;
			}
			i=index;
		}
		else if(2*i+1<allocsize){
			if(arr[i]>arr[2*i+1]){
				string tmp=arr[i];
				arr[i]=arr[2*i+1];
				arr[2*i+1]=tmp;
			}
			i=2*i+1;
		}
		else{
			break;
		}
	}
}
