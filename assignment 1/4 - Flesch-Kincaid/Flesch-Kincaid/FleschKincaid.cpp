/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "tokenscanner.h"
using namespace std;

/* Function prototypes */
void readtext();
void count(ifstream &in);
int countsyllables(string s);



/* constants */
double const C0=-15.59;
double const C1=0.39;
double const C2=11.8;

/* main function */
int main() {
	readtext();
    return 0;
}

/* this method return the number of syllables in the word */
int countsyllables(string s){
	int syllables=0;
	bool isvowel=false;			
	for(int i=0; i<s.length(); ++i){
		if(tolower(s[i])=='a' || tolower(s[i])=='e' || tolower(s[i])=='i' || tolower(s[i])=='o' || tolower(s[i])=='u' || tolower(s[i])=='y'){
			if(!(i==s.length()-1 && tolower(s[i])=='e') && !isvowel){
				++syllables;
			}
			isvowel=true;
		}
		else{
			isvowel=false;
		}
	}
	if(syllables==0)return 1;
	else return syllables;
}

/* this method counts syllables, words and sentences in the text */
void count(ifstream &in){
	TokenScanner scanner(in);
	scanner.ignoreWhitespace();
	scanner.addWordCharacters("'");
	int numwords=0;
	int numsentences=0;
	int syllables=0;
	while(scanner.hasMoreTokens()){
		string s=scanner.nextToken();
		if((s[0]>='a' && s[0]<='z') || (s[0]>='A' && s[0]<='Z')){
			++numwords;
			syllables+=countsyllables(s);
		}
		else if(s[0]=='?' || s[0]=='!' || s[0]=='.')++numsentences;
	}
	if(numwords==0)numwords=1;
	if(numsentences==0)numsentences=1;
	double grade=C0+C1*numwords/numsentences+C2*syllables/numwords;
	cout<<grade<<endl;
}

/* this method opens the text and does further manipulations on it */
void readtext(){
	ifstream in;
	while(true){
		string a=getLine();
		in.open(a.c_str());
		if(!in.fail()){
			break;
		}
		in.clear();
	}
	count(in);
}














