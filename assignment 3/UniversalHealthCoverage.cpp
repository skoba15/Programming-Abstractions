/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */

bool checkHospitals(Vector< Set<string> > & addedHospitals, Set<string> & location);

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);


int main() {

    return 0;
}

bool checkHospitals(Vector< Set<string> > & addedHospitals, Set<string> & location){
	for(int i=0; i<addedHospitals.size(); ++i){
		if(location==addedHospitals[i])return true;
	}
	return false;
}


bool canOfferUniversalCoverage(Set<string>& cities,Vector< Set<string> >& locations,int numHospitals,Vector< Set<string> >& result){
	if(numHospitals==0){
		Set<string> result2;
		for(int i=0; i<result.size(); ++i){
			result2+=result[i];
		}
		if(cities==result2)return true;
		else return false;
	}
	else{
		for(int i=0; i<locations.size(); ++i){
			Set<string> loc=locations[i];
			bool b=checkHospitals(result, loc);
			if(!b)result.add(loc);
			if(canOfferUniversalCoverage(cities, locations, numHospitals-1, result))return true;
			if(!b)result.remove(result.size()-1);
		}
	}
	return false;
}


