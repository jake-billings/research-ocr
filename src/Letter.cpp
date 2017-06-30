/*
 * Letter.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: jakebillings
 */

#include "Letter.h"

//Getters and setters
char Letter::getLetter() const {
	return letter;
}

void Letter::setLetter(char letter) {
	this->letter = letter;
}

const vector<vector<int> >& Letter::getMatrix() const {
	return matrix;
}

int Letter::getX() const {
	return x;
}

void Letter::setX(int x) {
	this->x = x;
}

int Letter::getY() const {
	return y;
}

void Letter::setY(int y) {
	this->y = y;
}

void Letter::setMatrix(const vector<vector<int> >& matrix) {
	this->matrix = matrix;
}

//Initialize a new letter object
Letter::Letter(vector < vector < int > > matrix) {
	this->matrix=matrix;
	this->x=0;
	this->y=0;
	this->letter='*';
}

