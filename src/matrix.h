/**
 * A header file for matrix.cpp
 * See matrix.cpp for docs.
 */

#include <vector>
#include <iostream>

#include "Letter.h"

#include <SFML/Graphics.hpp>

#pragma once

using namespace std;
using namespace sf;

const int THRESHOLD = 90;

const double RED_WEIGHT = 0.299;
const double GREEN_WEIGHT = 0.587;
const double BLUE_WEIGHT = 0.114;

vector< vector < int > > getGrayscalePixels(const Image& img);
vector< vector < int > > scaleMatrixTo(int width, int height, vector< vector < int > > oldMatrix);
void printMatrix (vector< vector < int > > matrix);
double compareMatrices(vector< vector < int > > matrixA, vector< vector < int > > matrixB);
vector< vector < int > > applyThreshold(const int& threshold, const vector< vector < int > > oldMatrix, int high, int low);
Image setPixels(const vector< vector < int > > matrix);
vector<Letter> findLetters(const int& threshold, const vector< vector < int > > matrix);
