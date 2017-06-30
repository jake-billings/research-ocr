//============================================================================
// Name        : CSCI261: Final Project - Text Recognition
// Author      : Jake Billings
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cmath>

#include "Letter.h"
#include "Alphabet.h"
#include "matrix.h"

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const string ALPHABET_IMAGE_FILE = "data/Font.png";
const string ALPHABET_TEXT_FILE = "data/Font.txt";
const string INPUT_IMAGE_FILE = "data/Input.png";

void doubleDraw(RenderWindow& rw, Drawable& d) {
	// Draw d to BOTH on-screen and off-screen framebuffers
	rw.draw(d);
	rw.display();
	rw.draw(d);
	rw.display();
}

int main() {
	//Load the sample alphabet to be used to recognize the input letters.
	Alphabet alphabet(ALPHABET_IMAGE_FILE,ALPHABET_TEXT_FILE);

	//Load the input text image
	Image inputImage;
	if (!inputImage.loadFromFile(INPUT_IMAGE_FILE)) {
		cerr << "Couldn't load input text image file " << INPUT_IMAGE_FILE << endl;
		return EXIT_FAILURE;
	}

	//Apply the threshold to the input text pixels
	vector< vector <int> > thresholdInputPixels = applyThreshold(THRESHOLD,getGrayscalePixels(inputImage),255,0);

	//Find the matrices of all input letters
	vector<Letter> inputLetterMatrices = findLetters(127, thresholdInputPixels);

	//For each letter found in the input image, find its best match in the sample alphabet
	for (int i = 0; i < inputLetterMatrices.size(); i++) {
		Letter match = alphabet.findBestMatch(inputLetterMatrices.at(i));
		cout << match.getLetter();
	}
	cout << endl;

	//Create an SFML window to display our images
	RenderWindow window(VideoMode(2500, 1000), "Text Recognition", Style::Titlebar | Style::Close);
	window.clear(Color::Black);

	//Declare a rectangle object to be used to draw outlines around letters
	RectangleShape rect(Vector2f(2500,500));

	//Draw the original alphabet image to the screen
	Texture alphabetTexture;
	Sprite alphabetSprite;
	alphabetTexture.loadFromImage(alphabet.getImage());
	alphabetSprite.setTexture(alphabetTexture);
	doubleDraw(window, alphabetSprite);

	//Draw the alphabet image with threshold applied to the screen
	Texture thresholdAlphabetTexture;
	Sprite thresholdAlphabetSprite;
	thresholdAlphabetTexture.loadFromImage(alphabet.getThresholdImage());
	thresholdAlphabetSprite.setTexture(thresholdAlphabetTexture);
	thresholdAlphabetSprite.setPosition(0,alphabetTexture.getSize().y);
	doubleDraw(window,thresholdAlphabetSprite);

	//Outline the recognized letters around the alphabet with the threshold applied
	for (int i = 0; i < alphabet.getLetters().size(); i++) {
		Letter letter = alphabet.getLetters().at(i);
		rect.setSize(Vector2f(letter.getMatrix().size(),letter.getMatrix().at(0).size()));
		rect.setPosition(letter.getX(),letter.getY()+alphabetTexture.getSize().y);
		rect.setFillColor(Color::Transparent);
		rect.setOutlineColor(Color::Green);
		rect.setOutlineThickness(1);
		doubleDraw(window,rect);
	}

	//Draw the input text image to the screen
	Texture inputTexture;
	Sprite inputSprite;
	inputTexture.loadFromImage(inputImage);
	inputSprite.setTexture(inputTexture);
	inputSprite.setPosition(0,alphabetTexture.getSize().y+thresholdAlphabetTexture.getSize().y);
	doubleDraw(window,inputSprite);

	//Draw the input text image with threshold applied to the screen
	Texture thresholdInputTexture;
	Sprite thresholdInputSprite;
	thresholdInputTexture.loadFromImage(setPixels(thresholdInputPixels));
	thresholdInputSprite.setTexture(thresholdInputTexture);
	thresholdInputSprite.setPosition(0,alphabetTexture.getSize().y+thresholdAlphabetTexture.getSize().y+inputTexture.getSize().y);
	doubleDraw(window,thresholdInputSprite);

	//Outline the recognized letters around the input text with the threshold applied
	for (int i = 0; i < inputLetterMatrices.size(); i++) {
		Letter letter = inputLetterMatrices.at(i);
		rect.setSize(Vector2f(letter.getMatrix().size(),letter.getMatrix().at(0).size()));
		rect.setPosition(letter.getX(),letter.getY()+alphabetTexture.getSize().y+thresholdAlphabetTexture.getSize().y+inputTexture.getSize().y);
		rect.setFillColor(Color::Transparent);
		rect.setOutlineColor(Color::Green);
		rect.setOutlineThickness(1);
		doubleDraw(window,rect);
	}

	//Display the SFML window
	while (window.isOpen()) {
		window.display();
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();
	}
}
