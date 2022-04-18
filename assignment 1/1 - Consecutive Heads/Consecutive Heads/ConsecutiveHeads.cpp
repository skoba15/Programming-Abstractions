/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

/*Function prototype */
int countturns();

/* main function */
int main() {
	cout<<"it took "<<countturns()<<" turns to get 3 consecutive heads."<<endl;
    return 0;
}


/*counts the number of turns to get 3 consecutive heads */
int countturns(){
	double p=0.5;
	int count=0;
	int heads=0;
	while(true){
		if(randomChance(p)){
			++heads;
			cout<<"heads"<<endl;
		}
		else{
			cout<<"tails"<<endl;
			heads=0;
		}
		++count;
		if(heads==3)break;
	}
	return count;
}
