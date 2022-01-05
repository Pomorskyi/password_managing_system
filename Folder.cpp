#pragma once
#include "Folder.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <conio.h>

namespace fs = std::filesystem;
using namespace std;

codingFiles::Folder::Folder(codingFiles::Coding code, string pat, string logFileName)
{
	this->codeOfLogFile = code;
	this->logFileName = "log.txt";
	this->path = pat;
	this->filesNum = 0;
	this->isClearFolder = true;

	for (const auto& entry : fs::directory_iterator(this->path)) {
		string file_path = entry.path().generic_string();
		if (file_path.find(this->logFileName) == string::npos) {
			filesPathes.add(file_path);
			this->filesNum++;
			this->isClearFolder = false;
		}
	}
}

void codingFiles::Folder::menu()
{
	cout << "Co chcesz zrobic?\n1. Stworzyc nowy plik z nowym haslem.\n2. Otworzyc istniejacy plik z folderu.\n";

	int wybor = -1;
	while (wybor <= 0 || wybor >= 3) {
		cout << "Twoj wybor: ";
		cin >> wybor;
	}

	switch (wybor) {
	case 1: {
		string newFileName = "";
		string pass = "";
		string SystemKodu = this->codeOfLogFile.getCodingField();
		cout << "Wpisz nazwe pliku (bez .txt): ";
		cin >> newFileName;
		newFileName += ".txt";
		cout << "Wpisz haslo dla pliku (te haslo bedzie zakodowane): ";
		cin >> pass;

		char zmieniamyKod = 'y';
		cout << "Czy chcesz zmienic systeme kodowania? (y/n)\nTerazniejszy system - to system pliku: " << this->logFileName << "\nTwoj wybor: ";
		cin >> zmieniamyKod;
		if (zmieniamyKod == 'y' && zmieniamyKod == 'Y') {
			cout << "Wprowadz system (wszytki znaki ktore beda zakodowane np. 'AbCdEfHdpgmwMKiosl236'): ";
			cin >> SystemKodu;
		}

		std::ofstream(this->path + newFileName);
		std::ofstream logStream;
		logStream.open(this->path + this->logFileName, std::ios::app);
		logStream << this->codeOfLogFile.code(this->path + newFileName) << "\n"
			<< this->codeOfLogFile.code(pass) << "\n"
			<< this->codeOfLogFile.code(SystemKodu) << "\n"
			<< this->codeOfLogFile.code(std::to_string(this->codeOfLogFile.getNumberOfSlides())) << "\n"
			<< this->codeOfLogFile.code(__TIMESTAMP__) << "\n"
			<< this->codeOfLogFile.code("*--**--**--**--*") << "\n";
		logStream.close();

		break;
	}
	case 2: {
		cout << "Pliki do wyboru w " << this->path << ": " << endl;
		if (this->filesNum > 0) {
			for (int i = 0; i < this->filesNum; i++) {
				cout << (i + 1) << ".\t" << this->filesPathes[i] << endl;
			}

			int wyborPliku = -1;
			while (wyborPliku < 1 || wyborPliku > filesPathes.getLenght()) {
				cout << "Wybor pliku: ";
				cin >> wyborPliku;
			}

			this->curPlik = Plik(filesPathes[wyborPliku - 1], this->path + this->logFileName, this->codeOfLogFile);

		}
		else {
			cout << "Nie mam zadnego pliku w folderze. Sprobuj stworzyc nowy plik" << endl;
			return;
		}
		break;
	}
	default:
		return;
	}

}
