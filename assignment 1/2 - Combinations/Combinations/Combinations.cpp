/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

/* Function prototypes */
int countC(int n, int k);

int main() {
    return 0;
}

/* this function counts the combination for given integers n and k */ 
int countC(int n, int k){
	if(k==0 || n==k)return 1;
	else return countC(n-1, k-1)+countC(n-1, k);
}
