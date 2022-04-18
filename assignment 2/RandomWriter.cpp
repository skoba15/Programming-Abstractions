/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"
using namespace std;

/* the maximum number of the symbols the generated text contains */
const int MAX_SYMBOLS=2000;

/* function prototypes */
void generatetext(string maxkey, Map<string, Vector<char> >& map);
void getinformationfromuser(ifstream & file, int & order);
void markovorder(ifstream & file, int order, string & maxkey, Map<string, Vector<char> > & map); 

/* the main function, which uses the main variables and methods for this problem */
int main() {
	ifstream a;
	int order;
	string maxkey;
	Map<string, Vector<char> > map;

	getinformationfromuser(a, order);
	markovorder(a, order, maxkey, map);
	generatetext(maxkey, map);
    return 0;
}


/* generates a random text based on the information of the method markovorder() */
void generatetext(string maxkey, Map<string, Vector<char> >& map){
	string randomtext=maxkey;
	string startsequence=maxkey;
	int symbols=MAX_SYMBOLS;
	while(true){
		if(!map.containsKey(startsequence))break;
		Vector<char> vect=map[startsequence];
		int index=0;
		char newchar;
		if(vect.isEmpty())break;
		double p=1/(double)(vect.size());
		while(true){
			if(randomChance(p)){
				newchar=vect[index];
				break;
			}
			++index;
			if(index>vect.size()-1)index=0;
		}
		randomtext+=newchar;
		startsequence+=newchar;
		startsequence=startsequence.substr(1);
		symbols--;
		if(symbols==0)break;
	}
	cout<<randomtext<<endl;
}


/* this method finds the frequencies for the sequences of the given size and symbols followed after them, finds the most frequent sequence */
void markovorder(ifstream &a, int order, string & maxkey, Map<string, Vector<char> > & map){
	int maxlength=0;
	string sequence="";
	int count=0;
	while(true){
		char c;
		a.get(c);
		if(a.fail())break;
		++count;
		sequence+=c;
		if(count==order){
			if(!map.containsKey(sequence)){
				Vector<char> v;
				char c;
				a.get(c);
				map.put(sequence, v);
				if(!a.fail()){
					map[sequence].add(c);
				}
				else break;
			}
			else{
				char c;
				a.get(c);
				if(!a.fail()){
					map[sequence].add(c);
				}
				else{
					if(map[sequence].size()==maxlength){
						maxkey=sequence;
					}
					break;
				}
			}
			
			for(int i=0; i<order; ++i){
				a.unget();
			}
			if(map[sequence].size()>maxlength){
				maxlength=map[sequence].size();
				maxkey=sequence;
			}
			sequence="";
			count=0;
		}
	}
}


/* this method asks the user to enter the name of the text file and the number of markov order */
void getinformationfromuser(ifstream & file, int & order){
	string text;
	while(true){
		text=getLine("enter text name: ");
		file.open(text.c_str());
		if(!file.fail())break;
		file.clear();
	}

	while(true){
		order=getInteger("enter the markov order [1-10]: ");
		if(order<1 || order>10)cout<<"value out of range"<<endl;
		else break;
	}
}