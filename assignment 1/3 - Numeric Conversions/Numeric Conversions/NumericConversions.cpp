/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;
/* Function prototypes */


string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
	cout<<intToString(-10)<<endl;
    return 0;
}

/* this method converts integer to string */
string intToString(int n){
	string s="";
	if(n<0)return "-"+intToString(-n);
	if(n/10==0){
		return s+(char)(n%10+'0');
	}
	else return intToString((n-n%10)/10)+s+(char)(abs(n)%10+'0');
}

/* this method converts string to int */
int stringToInt(string str){
	if(str.length()==1){
		return str[0]-'0';
	}
	else if(str[0]=='-'){
		return -1*stringToInt(str.substr(1));
	}
	else{
		return 10*stringToInt(str.substr(0, str.length()-1))+(str[str.length()-1]-'0');
	}
}
