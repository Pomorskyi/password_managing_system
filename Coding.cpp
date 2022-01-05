#pragma once
#include "Coding.h"
#include <iostream>
#include <string>

using namespace std;

int codingFiles::Coding::contains(char c)
{
	for (int i = 0; i < this->codingField.size(); i++) {
		if (c == this->codingField[i])
			return i;
	}
	return -1;
}

codingFiles::Coding::Coding(string field, int mas)
{
	this->codingField = field;
	this->numberOfSlides = mas;
}

string codingFiles::Coding::code(string data)
{
	string newString = "";
	for (int i = 0; i < data.size(); i++) {
		int curPosition = this->contains(data[i]);
		if (curPosition != -1) {
			int newChar = (curPosition + this->numberOfSlides) >= this->codingField.size() ?
				(curPosition + this->numberOfSlides - this->codingField.size()) :
				(curPosition + this->numberOfSlides) ;
			newString += this->codingField[newChar];
		}
		else {
			newString += data[i];
		}
	}
	return newString;
}

string codingFiles::Coding::decode(string data)
{
	string newString = "";
	for (int i = 0; i < data.size(); i++) {
		int curPosition = this->contains(data[i]);
		if (curPosition != -1) {
			int newChar = (curPosition - this->numberOfSlides) < 0 ?
				(curPosition - this->numberOfSlides + this->codingField.size()) :
				(curPosition - this->numberOfSlides);
			newString += this->codingField[newChar];
		}
		else {
			newString += data[i];
		}
	}
	return newString;
}
