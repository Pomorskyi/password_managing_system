#pragma once
#include <iostream>
#include <string>

using namespace std;

namespace codingFiles{
	class Coding{
	private:
		std::string codingField;
		int numberOfSlides;

		int contains(char);
	public: 
		Coding() : codingFiles::Coding("", 0) {};
		Coding(std::string, int);
		std::string getCodingField() { return this->codingField; };
		int getNumberOfSlides() { return this->numberOfSlides; };
		std::string code(std::string);
		std::string decode(std::string);
	};

}