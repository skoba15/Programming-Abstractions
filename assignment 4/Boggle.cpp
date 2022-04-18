/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "set.h"
#include <string>
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

const int STANDARD=16;
const int BIG=25;

/* Function prototypes */

struct coordinates{
	int x;
	int y;
};

void welcome();
void giveInstructions();
void chooseBoggleType(int & boardSize);
bool askToPlayAgain(GWindow & gw);
void fillBoard(Grid<char>& board, Vector<string>& cubes, int boardSize);
void swap(Vector<string>& cubes, int x, int i);
void letTheUserFill(Vector<string> & cubes, int boardSize);
void playerWords(Grid<char>& board, Set<string> & enteredwords);
bool playerWordValid(string word, Grid<char>& board, Lexicon& words, Set<string> & enteredWords);
bool canBeFoundOnBoard(string word, Grid<char>& board);
bool wordIsOnBoard(string word,Grid<char>& board, int i, int j, Set<string> & usedCharacters, string curword);
void highlightCubes(Set<string> & usedCharacters);
void unhighlightCubes(Set<string> & usedCharacters);
void computerWords(Grid<char>& board, Set<string> & playerwords);
void computerFindingWords(Grid<char>& board, int row, int column, Set<string> & playerwords, Set<string>& usedChars, Lexicon & words, string curword, Set<string>& usedwords);
void getRandomCubes(Vector<string> & cubes);
void getRandomSide(Grid<char> & board, Vector<string>& cubes);
void useConstantCubes(Vector<string> & cubes, int boardSize);
void enterCubes(Vector<string> &cubes, int boardSize);
bool checkMargins(int row, int column, Grid<char> &board);
string getCoordinates(int row, int column);
void makeStringUppercase(string & word);


/* Main program */
int main() {
	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
	while(true){
		initGBoggle(gw);
		welcome();
		giveInstructions();
		int boardSize;
		chooseBoggleType(boardSize);
		Vector<string> cubes;
		letTheUserFill(cubes, boardSize);
		drawBoard(boardSize, boardSize);
		Grid<char> board(boardSize, boardSize);
		Set<string> playerwords;
		fillBoard(board, cubes, boardSize);
		playerWords(board, playerwords);
		computerWords(board, playerwords);
		if(!askToPlayAgain(gw))break;
	}
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: enterCubes
 * Usage: enterCubes(Vector<string> &cubes, int boardSize);
 * --------------------------
 * lets the user enter cubes by printing strings of length 6
 */

void enterCubes(Vector<string> &cubes, int boardSize){
	int inputNumber=0;
	while(true){
		string cube=getLine("Please enter the sequence of letters of the cube: ");
		cubes.add(cube);
		if(inputNumber==boardSize*boardSize-1)break;
		++inputNumber;
	}
}

/*
 * Function: letTheUserFill
 * Usage: letTheUserFill(Vector<string> & cubes, int boardSize);
 * --------------------------
 * asks the user if they wish to fill the board
 */

void letTheUserFill(Vector<string> & cubes, int boardSize){
	while(true){
		string will=getLine("print yes if you wish to enter cubes yourself, else print no");
		if(will=="yes")break;
		else if(will=="no"){
			return;
		}
	}
	enterCubes(cubes, boardSize);
}

/*
 * Function: askToPlayAgain
 * Usage: askToPlayAgain(GWindow & gw);
 * --------------------------
 * asks the user if they want to play again;
 */

bool askToPlayAgain(GWindow & gw){
	while(true){
		string wish=getLine("would you like to play again?");
		if(wish=="yes"){
			gw.clear();
			return true;
		}
		else if(wish=="no")return false;
	}
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/*
 * Function: chooseBoggleType
 * Usage: chooseBoggleType(int & boardSize);
 * --------------------------
 * asks the user to choose the type of boggle--big or small
 */

void chooseBoggleType(int & boardSize){
	while(true){
		string wish=getLine("would you like to play on 5X5 board? answer yes or no");
		if(wish=="yes"){
			boardSize=5; 
			break;
		}
		else if(wish=="no"){
			boardSize=4; 
			break;
		}
	}
}

/*
 * Function: swap
 * Usage: swap(Vector<string>& cubes, int x, int i);
 * --------------------------
 * swaps the elements of the vector
 */

void swap(Vector<string>& cubes, int x, int i){
	string s=cubes[x];
	cubes[x]=cubes[i];
	cubes[i]=s;
}

/*
 * Function: getRandomCubes
 * Usage: getRandomCubes(Vector<string> & cubes)
 * --------------------------
 * puts the cubes on the board in a random way
 */

void getRandomCubes(Vector<string> & cubes){
	for(int i=0; i<cubes.size(); ++i){
		int x=randomInteger(i, cubes.size()-1);
		swap(cubes, x, i);
	}
}

/*
 * Function: getRandomSide
 * Usage: getRandomSide(Grid<char> & board, Vector<string>& cubes)
 * --------------------------
 * chooses a random side of the cube
 */

void getRandomSide(Grid<char> & board, Vector<string>& cubes){
	int vectorIndex=0;
    for(int i=0; i<board.numRows(); ++i){
		for(int j=0; j<board.numCols(); ++j){
			int number=randomInteger(0, 5);
			char letter=cubes[vectorIndex][number];
			board.set(i, j, letter);
			labelCube(i, j, letter);
			vectorIndex++;
		}
	}
}

/*
 * Function: useConstantCubes
 * Usage: useConstantCubes(Vector<string> & cubes, int boardSize)
 * --------------------------
 * if the user doesn't wish to fill the board, it will be filled automatically with constant cubes
 */

void useConstantCubes(Vector<string> & cubes, int boardSize){
	if(cubes.size()==0){
		for(int i=0; i<boardSize*boardSize; ++i){
			(boardSize==4) ? cubes.add(STANDARD_CUBES[i]) : cubes.add(BIG_BOGGLE_CUBES[i]);
		}
	}
}

/*
 * Function: fillBoard
 * Usage: fillBoard(Grid<char>& board, Vector<string> & cubes, int boardSize)
 * --------------------------
 * fills the board
 */

void fillBoard(Grid<char>& board, Vector<string> & cubes, int boardSize){
	useConstantCubes(cubes, boardSize);
	getRandomCubes(cubes);
	getRandomSide(board, cubes);
}

/*
 * Function: unhighlightCubes
 * Usage: unhighlightCubes(Set<string> & usedCharacters)
 * --------------------------
 * unhighlights all the highlited letters
 */

void unhighlightCubes(Set<string> & usedCharacters){
	foreach(string s in usedCharacters){
		int row=(int)(s[0]-'0');
		int column=(int)(s[1]-'0');
		highlightCube(row, column, false);
	}
}

/*
 * Function: highlightCubes
 * Usage: highlightCubes(Set<string> & usedCharacters)
 * --------------------------
 * highlights all the letters of the found word
 */

void highlightCubes(Set<string> & usedCharacters){
	foreach(string s in usedCharacters){
		int row=(int)(s[0]-'0');
		int column=(int)(s[1]-'0');
		highlightCube(row, column, true);
	}
}

/*
 * Function: checkMargins
 * Usage: checkMargins(int row, int column, Grid<char> &board)
 * --------------------------
 * checks if the coordinates are inside the board
 */

bool checkMargins(int row, int column, Grid<char> &board){
	return row>=0 && row<=board.numRows()-1 && column>=0 && column<=board.numCols()-1;
}

/*
 * Function: getCoordinates
 * Usage: getCoordinates(int row, int column)
 * --------------------------
 * returns a string of length 2. the first character is the row and the second one is the column.
 */

string getCoordinates(int row, int column){
	string coord="";
	coord+=(char)('0'+row);
	coord+=(char)('0'+column);
	return coord;
}

/*
 * Function: wordIsOnBoard
 * Usage: wordIsOnBoard(string word,Grid<char>& board, int i, int j, Set<string> & usedCharacters, string curword)
 * --------------------------
 * checks recursively if the word without the first character can be constructed on the board
 */

bool wordIsOnBoard(string word,Grid<char>& board, int i, int j, Set<string> & usedCharacters, string curword){
	if(word==""){
		highlightCubes(usedCharacters);
		recordWordForPlayer(curword, HUMAN);
		unhighlightCubes(usedCharacters);
		return true;
	}
	else{
		for(int a=-1; a<=1; ++a){
			for(int b=-1; b<=1; ++b){
				if(a!=0 || b!=0){
					if(checkMargins(i+a, j+b, board)){
						string coord=getCoordinates(i+a, b+j);
						if(!usedCharacters.contains(coord) && board[i+a][b+j]==word[0]){
							usedCharacters.add(coord);
							if(wordIsOnBoard(word.substr(1), board, i+a, j+b, usedCharacters, curword+word[0])) return true;
							usedCharacters.remove(coord);
						}
					}
				}
			}
		}
	}
	return false;
}

/*
 * Function: canBeFoundOnBoard
 * Usage: canBeFoundOnBoard(string word, Grid<char>& board)
 * --------------------------
 * checks if the entered word can be constructed
 */

bool canBeFoundOnBoard(string word, Grid<char>& board){
	Set<string> usedCharacters;
	for(int i=0; i<board.numRows(); ++i){
		for(int j=0; j<board.numCols(); ++j){
			if(board[i][j]==word[0]){
				string coord=getCoordinates(i, j);
				string curword="";
				curword+=+word[0];
				usedCharacters.add(coord);
				if(wordIsOnBoard(word.substr(1), board, i, j, usedCharacters, curword))return true;
				usedCharacters.remove(coord);
			}
		}
	}
	return false;
}

/*
 * Function: playerWordValid
 * Usage: playerWordValid(string word, Grid<char>& board, Lexicon & words, Set<string> & enteredWords)
 * --------------------------
 * checks if the entered word is valid
 */

bool playerWordValid(string word, Grid<char>& board, Lexicon & words, Set<string> & enteredWords){
	if(word.length()>=4 && words.contains(word) && !enteredWords.contains(word)){
		if(canBeFoundOnBoard(word, board))return true;
	}
	return false;
}

/*
 * Function: makeStringUppercase
 * Usage: makeStringUppercase(string & word)
 * --------------------------
 * makes the whole world uppercase
 */

void makeStringUppercase(string & word){
	for(int i=0; i<word.length(); ++i){
		word[i]=toupper(word[i]);
	}	
}

/*
 * Function: playerWords
 * Usage: playerWords(Grid<char>& board, Set<string> & enteredwords)
 * --------------------------
 * let the user play the game and enter the words
 */

void playerWords(Grid<char>& board, Set<string> & enteredwords){
	Lexicon words("EnglishWords.dat");
	while(true){
		string word=getLine("Please enter your word: ");
		if(word=="")break;
		makeStringUppercase(word);
		if(playerWordValid(word, board, words, enteredwords)){
			enteredwords.add(word);
		}
		else cout<<"that word is invalid, or you've already used it, try again!"<<endl;
	}
}

/*
 * Function: computerFindingWords
 * Usage: computerFindingWords(Grid<char>& board, int row, int column, Set<string> & playerwords, Set<string>& usedChars, Lexicon & words, string curword, Set<string> &usedwords)
 * --------------------------
 * finds all words that can be constructed from the given first character on the board
 */

void computerFindingWords(Grid<char>& board, int row, int column, Set<string> & playerwords, Set<string>& usedChars, Lexicon & words, string curword, Set<string> &usedwords){
	if(!words.containsPrefix(curword)){
		return;
	}
	if(words.contains(curword)){
		if(curword.length()>=4 && !playerwords.contains(curword) && !usedwords.contains(curword)){
			recordWordForPlayer(curword, COMPUTER);
			usedwords.add(curword);
		}
	}
	for(int a=-1; a<=1; ++a){
			for(int b=-1; b<=1; ++b){
				if(a!=0 || b!=0){
					if(checkMargins(row+a, column+b, board)){
						string coord=getCoordinates(row+a, column+b);
						if(!usedChars.contains(coord)){
							usedChars.add(coord);
							computerFindingWords(board, row+a, column+b, playerwords, usedChars, words, curword+board[row+a][column+b], usedwords);
							usedChars.remove(coord);
						}
					}
				}
			}
		}
	return;
}

/*
 * Function: computerWords
 * Usage: computerWords(Grid<char>& board, Set<string> & playerwords)
 * --------------------------
 * finds all valid words, which are not used by the user, on the board
 */

void computerWords(Grid<char>& board, Set<string> & playerwords){
	Lexicon words("EnglishWords.dat");
	Set<string> usedwords;
	for(int i=0; i<board.numRows(); ++i){
		for(int j=0; j<board.numCols(); ++j){
			Set<string> usedChars;
			string coord=getCoordinates(i, j);
			usedChars.add(coord);
			string curword="";
			computerFindingWords(board, i, j, playerwords, usedChars, words, curword, usedwords);
		}
	}
}

