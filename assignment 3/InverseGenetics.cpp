/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);
void returnRnas(string protein, Map<char, Set<string> >& codons, Set<string>& rnas, string codon);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	listAllRNAStrandsFor("FLI", codons);
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}


void returnRnas(string protein, Map<char, Set<string> >& codons, Set<string>& rnas, string codon){
	if(protein==""){
		rnas.add(codon);
	}
	else{
		char ch=protein[0];
		Set<string> cod=codons[ch];
		foreach(string s in cod){
			returnRnas(protein.substr(1), codons, rnas, codon+s);
		}
	}
}


void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	Set<string> rnas;
	string codon="";
	returnRnas(protein, codons, rnas, codon);
	foreach(string codonn in rnas){
		cout<<codonn<<endl;
	}
}
