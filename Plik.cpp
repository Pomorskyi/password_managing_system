#pragma once
#include "Plik.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using std::string;
using std::cout;
using std::endl;
using std::cin;

codingFiles::MyList<string> codingFiles::Plik::aktulizacja()
{
	MyList<string> decodedLogText = MyList<string>();
	std::string liniaLog = "";
	std::ifstream czytanieLog(this->log_path);
	if (czytanieLog.is_open())
	{
		while (getline(czytanieLog, liniaLog))
		{
			decodedLogText.add(this->kod.decode(liniaLog));
		}
	}
	czytanieLog.close();

	this->text.clear();
	std::string liniaPlik = "";
	std::ifstream czytaniePliku(this->path);
	if (czytaniePliku.is_open())
	{
		while (getline(czytaniePliku, liniaPlik))
		{
			this->text.add(this->kod.decode(liniaPlik));
		}
	}
	czytaniePliku.close();
	return decodedLogText;
}

codingFiles::Plik::Plik(string p, string log, Coding c)
{
	this->ketogorieSTRINGS = MyList<string>();
	this->ketogorieSTRINGS.add("FaceBook");
	this->ketogorieSTRINGS.add("Messenger");
	this->ketogorieSTRINGS.add("WhatsUp");
	this->ketogorieSTRINGS.add("AppleDeveloper");
	this->ketogorieSTRINGS.add("GoogleAccount");
	this->ketogorieSTRINGS.add("VisualStudio");
	this->ketogorieSTRINGS.add("IntelJIdea");
	this->path = p;
	this->log_path = log;
	this->czyHasloPrawidlowe = false;
	this->lastLogin = "";
	this->kod = c;
	this->text = MyList<string>();

	MyList<string> decodedLogText = this->aktulizacja();

	int indexOfFile = 0;
	for (int i = 0; i < decodedLogText.getLenght(); i += 6) {
		if (decodedLogText[i] == this->path) {
			indexOfFile = i;
			break;
		}
	}
	this->decodedHaslo = decodedLogText[indexOfFile + 1];
	this->lastLogin = decodedLogText[indexOfFile + 4];
	this->rewizjaHasla(decodedLogText, indexOfFile);
}

void codingFiles::Plik::rewizjaHasla(MyList<string> decodedLogText, int indexOfFile)
{
	string wprowadzoneHaslo = "";
	int i = 3;
	while (!this->czyHasloPrawidlowe && i != 0) {
		cout << "Wprowadz haslo od pliku " << this->path << "(masz " << i << " sproby): ";
		cin >> wprowadzoneHaslo;
		i--;

		if (wprowadzoneHaslo == this->decodedHaslo) {
			this->czyHasloPrawidlowe = true;
			cout << "		--HASLO POPRAWNE--" << endl;
			cout << "Ostatnie poprawne logowanie: " << this->lastLogin << endl;

			std::ofstream out;
			out.open(this->log_path);
			if (out.is_open())
			{
				for (int i = 0; i < decodedLogText.getLenght(); i++) {
					if (i == indexOfFile + 4) {
						out << this->kod.code(__TIMESTAMP__) << endl;
					}
					else {
						out << this->kod.code(decodedLogText[i]) << endl;
					}
					
				}
			}

			out.close();

			this->menu();
		}
	}
	cout << "Ty nie jestes wlascicielem tego pliku. Haslo nie jest poprawne" << endl;
	return;
}

void codingFiles::Plik::menu()
{
	if (this->czyHasloPrawidlowe) {
		cout << "		WYBIERZ OPCJE" << endl;
		cout << "1. Wyszukaj hasla z danej kategorii" << endl;
		cout << "2. Posortuj hasla wedlug 2 roznych parametrow" << endl;
		cout << "3. Dodaj albo usun hasla pojedynczo" << endl;
		cout << "4. Dodaj nowe kategorii albo usun kategorie wraz ze wszystkimi przypisanymi haslami" << endl; 
		cout << "5. Pokazac hasla" << endl; 
		cout << "		Zeby wyjszcz kliknij w gorze po prawej stronie czerwony przycisk " << endl; 
		int wybor = -1;

		while (wybor < 1 || wybor > 5) {
			cin >> wybor;
		}
		switch (wybor)
		{
		case 1: {
			szukaj();
			break;
		}
		case 2: {
			sortuj2Kategorii <codingFiles::Haslo> ();
			break;
		}
		case 3: {
			haslaPojedynczo();
			break;
		}
		case 4: {
			haslaKategorii();
			break;
		}
		case 5: {
			showHasla();
			break;
		}
		default: {
			return;
			break;
		}
		}
	}
	this->menu();
}

void codingFiles::Plik::szukaj()
{
	int kat = -1;
	do {
		cout << "Wybierz kategorie: " << endl;
		for (int i = 1; i <= this->ketogorieSTRINGS.getLenght(); i++) {
			cout << i << ". " << this->ketogorieSTRINGS[i - 1] << endl;
		}
		cin >> kat;
		kat--;
	} while (!(kat >= 0 && this->ketogorieSTRINGS.getLenght()));

	MyList<Haslo> hasla = getHasla();

	cout << "==============================================================================" << endl;
	for (int i = 0, j = 0; i < hasla.getLenght(); i++) {
		if (hasla[i].kategoria == kat) {
			cout << j++ << ". " << hasla[i].nazwa << "\t\t"
				<< hasla[i].haslo << "\t\t"
				<< this->ketogorieSTRINGS[hasla[i].kategoria] << "\t\t"
				<< hasla[i].dodatkowe << endl;
		}
	}
	cout << "==============================================================================" << endl;
	this->menu();
}

int codingFiles::Plik::compareTo(codingFiles::Haslo n1, codingFiles::Haslo n2) {
	if (this->ketogorieSTRINGS[n1.kategoria] > this->ketogorieSTRINGS[n2.kategoria]) {
		return 1;
	}else if (this->ketogorieSTRINGS[n1.kategoria] < this->ketogorieSTRINGS[n2.kategoria]) {
		return -1;
	}else if (n1.haslo.length() > n2.haslo.length()) {
		return 1;
	}else if (n1.haslo.length() < n2.haslo.length()) {
		return -1;
	}else if (n1.haslo.length() == n2.haslo.length()) {
		return 0;
	}
}

template <typename T>
void codingFiles::Plik::sortuj2Kategorii()
{
	MyList<Haslo> hasla = this->getHasla();

	int i, j;
	for (i = 0; i < hasla.getLenght() - 1; i++) {
		for (j = 0; j < hasla.getLenght() - i - 1; j++)
			if (codingFiles::Plik::compareTo(hasla[j], hasla[j + 1]) == 1)
				hasla.swaping(j, j + 1);
	}

	std::ofstream out;
	out.open(this->path);
	if (out.is_open())
	{
		for (int i = 0; i < hasla.getLenght(); i++) {
			string dlaKodowania = hasla[i].nazwa + ", " + hasla[i].haslo + ", " + std::to_string(hasla[i].kategoria) + ", " + hasla[i].dodatkowe;
			out << this->kod.code(dlaKodowania) << endl;
		}
	}

	out.close();
}

void codingFiles::Plik::haslaPojedynczo()
{
	cout << "1. Dodac nowe haslo\n2. Usunac istniejace haslo z pliku" << endl;
	int wybor = -1;
	while (wybor < 1 || wybor > 2) {
		cout << "Twoj wybor: ";
		cin >> wybor;
	}
	switch (wybor)
	{
	case 1: {
		string naz = "", has = "", add = "";
		int kat = 0;
		cout << "Wprowadz nazwe: ";
		cin >> naz;
		cout << "Wprowadz haslo: ";
		cin >> has;

		do{
			cout << "Wybierz kategorie: " << endl;
			for (int i = 1; i <= this->ketogorieSTRINGS.getLenght(); i++) {
				cout << i << ". " << this->ketogorieSTRINGS[i - 1] << endl;
			}
			cin >> kat;
			kat--;
		} while (!(kat >=0 && kat < this->ketogorieSTRINGS.getLenght()));
		char czyDodatek = false;
		cout << "Czy chcesz wprowadzic dodatkowe? (y/n)";
		cin >> czyDodatek;
		czyDodatek = tolower(czyDodatek);
		if (czyDodatek == 'y') {
			cout << "Prosze: ";
			cin >> add;
		}
		
		std::ofstream out_stream;
		out_stream.open(this->path, std::ios::app);
		string dlaKodowania = naz + ", " + has + ", " + std::to_string(kat) + ", " + add;
		out_stream << this->kod.code(dlaKodowania) << endl;
		out_stream.close();
		break;
	}
	case 2: {
		MyList<Haslo> hasla = getHasla();
		
		if (hasla.getLenght() > 0) {
			cout << "==============================================================================" << endl;
			for (int i = 0; i < hasla.getLenght(); i++) {
				cout << i << ". " << hasla[i].nazwa << "\t\t"
					<< hasla[i].haslo << "\t\t"
					<< this->ketogorieSTRINGS[hasla[i].kategoria] << "\t\t"
					<< hasla[i].dodatkowe << endl;
			}
			cout << "==============================================================================" << endl;
			int wybor = -1;
			while (wybor < 0 || wybor > hasla.getLenght()) {
				cin >> wybor;
			}

			hasla.deleteByIndex(wybor);

			std::ofstream out;
			out.open(this->path);
			if (out.is_open())
			{
				for (int i = 0; i < hasla.getLenght(); i++) {
					string dlaKodowania = hasla[i].nazwa + ", " + hasla[i].haslo + ", " + std::to_string(hasla[i].kategoria) + ", " + hasla[i].dodatkowe;
					out << this->kod.code(dlaKodowania) << endl;
				}
			}

			out.close();
		}
		else {
			cout << "Nie mam zadnego hasla" << endl;
		}
		break;
	}
	default:
		return;
	}
	this->aktulizacja();
}

void codingFiles::Plik::haslaKategorii()
{
	cout << "1. Dodac nowe kategorii\n2. Usunac istniejace kategorii z pliku" << endl;
	int wybor = -1;
	while (wybor < 1 || wybor > 2) {
		cout << "Twoj wybor: ";
		cin >> wybor;
	}

	int kat = -1;
	do {
		cout << "Wybierz kategorie: " << endl;
		for (int i = 1; i <= this->ketogorieSTRINGS.getLenght(); i++) {
			cout << i << ". " << this->ketogorieSTRINGS[i - 1] << endl;
		}
		cin >> kat;
		kat--;
	} while (!(kat >= 0 && this->ketogorieSTRINGS.getLenght()));
	
	switch (wybor)
	{
		case 1: {
			char jeszcze = ' ';
			do {
				string naz = "", has = "", add = "";
				cout << "Wprowadz nazwe: ";
				cin >> naz;
				cout << "Wprowadz haslo: ";
				cin >> has;

				char czyDodatek = false;
				cout << "Czy chcesz wprowadzic dodatkowe? (y/n)";
				cin >> czyDodatek;
				czyDodatek = tolower(czyDodatek);
				if (czyDodatek == 'y') {
					cout << "Prosze: ";
					cin >> add;
				}

				std::ofstream out_stream;
				out_stream.open(this->path, std::ios::app);
				string dlaKodowania = naz + ", " + has + ", " + std::to_string(kat) + ", " + add;
				out_stream << this->kod.code(dlaKodowania) << endl;
				out_stream.close();
				cout << "Czy chcesz wprowadzic jeszcze jedno hasle w kategorii " << this->ketogorieSTRINGS[kat] << "? (y/n)";
				cin >> jeszcze;
				jeszcze = tolower(jeszcze);
			} while (jeszcze == 'y');
			break;
		}
		case 2: {
			MyList<Haslo> hasla = getHasla();

			if (hasla.getLenght() > 0) {
				for (int i = 0; i < hasla.getLenght(); i++) {
					if (hasla[i].kategoria == kat) {
						hasla.deleteByIndex(i--);
					}
				}

				std::ofstream out;
				out.open(this->path);
				if (out.is_open())
				{
					for (int i = 0; i < hasla.getLenght(); i++) {
						string dlaKodowania = hasla[i].nazwa + ", " + hasla[i].haslo + ", " + std::to_string(hasla[i].kategoria) + ", " + hasla[i].dodatkowe;
						out << this->kod.code(dlaKodowania) << endl;
					}
				}

				out.close();
			}
			else {
				cout << "Nie mam zadnego hasla" << endl;
			}
			break;
		}
		default: {
			return;
			break;
		}
	}
	this->aktulizacja();
}

void codingFiles::Plik::showHasla()
{
	cout << "==============================================================================" << endl;
	MyList<Haslo> hasla = this->getHasla();
	for (int i = 0; i < hasla.getLenght(); i++) {
		cout << hasla[i].nazwa << "\t\t"
			<< hasla[i].haslo << "\t\t"
			<< this->ketogorieSTRINGS[hasla[i].kategoria] << "\t\t"
			<< hasla[i].dodatkowe << endl;
	}
	cout << "==============================================================================" << endl;
	this->menu();
}

string* codingFiles::Haslo::delim(string p)
{
	string* slowa = new string[4];
	int* delPos = new int[3];
	for (int i = 0, j = 0; i < p.length() - 1; i++) {
		if (p[i] == ',' && p[i + 1] == ' ') {
			delPos[j++] = i;
		}
	}
	slowa[0] = p.substr(0,delPos[0]);
	slowa[1] = p.substr(delPos[0] + 2,delPos[1] - delPos[0] - 2);
	slowa[2] = p.substr(delPos[1] + 2, delPos[2] - delPos[1] - 2);
	if (delPos[2] + 2 < p.length()) {
		slowa[3] = p.substr(delPos[2] + 2);
	}
	else {
		slowa[3] = "";
	}

	return slowa;
}

codingFiles::MyList<codingFiles::Haslo> codingFiles::Plik::getHasla()
{
	MyList<Haslo> hasla = MyList<Haslo>();

	std::string l = "";
	std::ifstream czytanie(this->path);
	if (czytanie.is_open())
	{
		while (getline(czytanie, l))
		{
			string* slowa = codingFiles::Haslo::delim(this->kod.decode(l));
			hasla.add(Haslo{ slowa[0], slowa[1], stoi(slowa[2]), slowa[3] });
		}
	}
	czytanie.close();
	return hasla;
}