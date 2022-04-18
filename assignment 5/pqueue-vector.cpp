/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
#include <iostream>
#include "pqueue-vector.h"
#include "vector.h"
#include "error.h"


/* constructor */
VectorPriorityQueue::VectorPriorityQueue() {
	
}

/* destructor */
VectorPriorityQueue::~VectorPriorityQueue() {
	
}

/* returns the size of the queue */
int VectorPriorityQueue::size() {
	return vect.size();
}


/* returns true if the queue is empty */
bool VectorPriorityQueue::isEmpty() {
	return vect.size()==0;
}

/* adds new value to the queue */
void VectorPriorityQueue::enqueue(string value) {
	vect.add(value);
}

/* returns the minimal element */
string VectorPriorityQueue::peek() {
	if(vect.size()==0)error("there is no element in priority queue!");
	else{
		string minstr;
		for(int i=0; i<vect.size(); ++i){
			if(i==0)minstr=vect[i];
			else{
				if(vect[i]<minstr)minstr=vect[i];
			}
		}
		return minstr;
	}
}

/* returns the minimal element and removes it from the queue */
string VectorPriorityQueue::dequeueMin() {
	if(vect.size()==0)error("there is no element in priority queue");
	else{
		string minstr;
		int index=0;
		for(int i=0; i<vect.size(); ++i){
			if(i==0)minstr=vect[i];
			else{
				if(vect[i]<minstr){
					minstr=vect[i];
					index=i;
				}
			}
		}
		vect.remove(index);
		return minstr;
	}
}

