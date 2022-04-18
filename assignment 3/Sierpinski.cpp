/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
#include <math.h>
using namespace std;

void SierpinskiTriangle(double size, int order, double x, double y, GWindow & gw);

int main() {
    GWindow gw;
	int order;
	double size;
	while(true){
		order=getInteger("please enter the fractal order: ");
		size=getInteger("please enter the size of the triangle side: ");
		if(order<0 || size<=0)cout<<"invalid numbers, try again";
		else break;
	}
	double x=gw.getWidth()/2;
	double y=gw.getHeight()/2-size/sqrt(3.0);
	SierpinskiTriangle(size, order, x, y, gw);
    return 0;
}

void SierpinskiTriangle(double size, int order, double x, double y, GWindow & gw){
	if(order==0){
		GPoint p1=gw.drawPolarLine(x, y, size, -60);
		GPoint p2=gw.drawPolarLine(p1, size, 180);
		GPoint p3=gw.drawPolarLine(p2, size, 60);
	}
	else{
		SierpinskiTriangle((double)(size)/2, order-1, x+(double)(size)/4, y+(double)(size)*sqrt(3.0)/4, gw);
		SierpinskiTriangle((double)(size)/2, order-1, x-(double)(size)/4, y+(double)(size)*sqrt(3.0)/4, gw);
		SierpinskiTriangle((double)(size)/2, order-1, x, y, gw);
	}
}
