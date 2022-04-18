/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "simpio.h"
#include "queue.h"
#include "lexicon.h"
#include "vector.h"
using namespace std;

/* function prototypes */
void addnewwordsinqueue(Vector<string>& nextwords, Queue< Vector<string> > & ladder, Vector<string> & path);
void printpath(Vector<string> &path);
void nextpathwords(string word, Vector<string> & nextwords, Set<string> &passedwords, Lexicon &data);
void findpath(string startingword, string endword);


/*main function, which lets the user write the input, the starting word and the ending word, then it finds the path if one exists*/
int main() {
	while(true){
		string startingword=getLine("Enter the starting word(or nothing to quit): ");
		if(startingword=="")break;
		string endword=getLine("Enter the ending word: ");
		cout<<"Searching..."<<endl;
		findpath(startingword, endword);
	}
    return 0;
}

/* prints the found path */
void printpath(Vector<string>& path){
	cout<<"Ladder found: ";
	for(int i=0; i<path.size(); ++i){
		if(i!=0)cout<<"-->";
		cout<<path[i];
		if(i==path.size()-1)cout<<endl;
	}
}

/*this method searches all the words which differ with only one letter from the given word and saves them in the set */
void nextpathwords(string word, Vector<string> &nextwords, Set<string> &passedwords, Lexicon &data){
	passedwords.add(word);
	for(char ch='a'; ch<='z'; ++ch){
		for(int i=0; i<word.length(); ++i){
			string s=word;
			s[i]=ch;
			if(!passedwords.contains(s) && data.contains(s)){
				nextwords.add(s);
				passedwords.add(s);
			}
		}
	}
}

/* adds new paths in the queue */
void addnewwordsinqueue(Vector<string> & nextwords, Queue< Vector<string> >& ladder, Vector<string> &path){
	for(int i=0; i<nextwords.size(); ++i){
		Vector<string> copy=path;
		copy.add(nextwords[i]);
		ladder.enqueue(copy);
	}
}


/* the method tries to find the word ladder between the starting and ending words */
void findpath(string startingword, string endword){
	Lexicon english("EnglishWords.dat");
	if(!english.contains(startingword) || !english.contains(endword)){
		cout<<"invalid english words, try again"<<endl;
		return;
	}
	Set<string> passedwords;
	Vector<string> nextwords;
	Queue< Vector<string> > ladder;
	Vector<string> path1;
	path1.add(startingword);
	ladder.enqueue(path1);
	Vector<Vector<string> > vect1;
	while(!ladder.isEmpty()){
		nextwords.clear();
		Vector<string> path=ladder.dequeue();
		if(path[path.size()-1]==endword){
			printpath(path);
			return;
		}
		nextpathwords(path[path.size()-1], nextwords, passedwords, english);
		addnewwordsinqueue(nextwords, ladder, path);
	}
	cout<<"can't find the path"<<endl;
}
