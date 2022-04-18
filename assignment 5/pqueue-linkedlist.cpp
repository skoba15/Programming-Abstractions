/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"
#include "vector.h"

/* constructor, initializes start and last poineters and the size */
LinkedListPriorityQueue::LinkedListPriorityQueue() {
	length=0;
	start=NULL;
	last=NULL;
}

/* destructor, deletes everything in thr heap */
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	free(start);
}

/* returns the size of the queue */
int LinkedListPriorityQueue::size() {
	return length;
}

/* returns true if the queue is empty */
bool LinkedListPriorityQueue::isEmpty() {
	return length==0;
}

/* adds new elements to the qeueue */
void LinkedListPriorityQueue::enqueue(string value) {
	if(length==0){
		start=new elem;
		start->name=value;
		start->link=NULL;
		last=start;
	}
	else{
		bool added=false;
		elem * previous=start;
		for(elem * p=start; p!=NULL; p=p->link){
			if(value<p->name){
				if(p==start){
					start=new elem;
					start->link=p;
					start->name=value;
					added=true;
					break;
				}
				else{
					previous->link=new elem;
					elem * po=previous->link;
					po->name=value;
					po->link=p;
					added=true;
					break;
				}
			}
			previous=p;
		}
		if(!added){
			elem * e=new elem;
			e->link=NULL;
			e->name=value;
			last->link=e;
			last=e;
		}
	}
	++length;
}

/* returns the minimal element in the queue */
string LinkedListPriorityQueue::peek() {
	if(length==0){
		error("there is no element in priority queue");
	}
	else{
		return start->name;
	}
}

/* returns the minimal element from the queue and removes it */
string LinkedListPriorityQueue::dequeueMin() {
	if(length==0){
		error("there is no element in priority queue");
	}
	else{
		elem * e=start->link;
		string s=start->name;
		start=e;
		length--;
		return s;
	}
}

/* frees the heap memory */
void LinkedListPriorityQueue:: free(elem * start){
	if(start==NULL){
		return;
	}
	free(start->link);
	delete start;
}