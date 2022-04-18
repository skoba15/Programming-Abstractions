/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"
#include "vector.h"

/* constructor, initializes start pointer and sets the size to zero */
DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	start=NULL;
	length=0;
}

/* destructor, frees the memory of the heap */
DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	free(start);
}

/* returns the size of the queue */
int DoublyLinkedListPriorityQueue::size() {
	return length;
}

/* returns true if the queeu is empty */
bool DoublyLinkedListPriorityQueue::isEmpty() {
	return length==0;
}

/* adds new values to the queue */
void DoublyLinkedListPriorityQueue::enqueue(string value) {
	if(start==NULL){
		start=new str;
		start->previous=NULL;
		start->next=NULL;
		start->name=value;
	}
	else{
		str * s=start;
		start=new str;
		s->previous=start;
		start->next=s;
		start->previous=NULL;
		start->name=value;
	}
	++length;
}


/* returns the minimal element from the queue */
string DoublyLinkedListPriorityQueue::peek() {
	if(length==0){
		error("there si no elelemt in priority queue");
	}
	string min=start->name;
	for(str * p=start; p!=NULL; p=p->next){
		if(p->name<min){
			min=p->name;
		}
	}
	return min;
}

/* returns the minimal element from the queue and removes it */
string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(length==0){
		error("there is no elelemt in priority queue");
	}
	string min=start->name;
	str * po=start;
	for(str * p=start; p!=NULL; p=p->next){
		if(p->name<min){
			min=p->name;
			po=p;
		}
	}
	if(po->previous==NULL && po->next==NULL){
		delete po;
		start=NULL;
	}
	else if(po->previous==NULL && po->next!=NULL){
		str * pp=po->next;
		start=pp;
		pp->previous=NULL;
		delete po;
	}
	else if(po->previous!=NULL && po->next==NULL){
		po->previous->next=NULL;
		delete po;
	}
	else{
		po->previous->next=po->next;
		po->next->previous=po->previous;
		delete po;
	}
	length--;
	return min;
}

/* frees the memeory of the heap */
void DoublyLinkedListPriorityQueue::free(str * start){
	if(start==NULL){
		return;
	}
	free(start->next);
	delete start;
}