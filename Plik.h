#pragma once
#include <iostream>
#include <string>
#include "Coding.h"
#include "MyList.h"

namespace codingFiles {
	struct Haslo {
		string nazwa;
		string haslo;
		int kategoria;
		string dodatkowe;

		static string* delim(string);
	};
	enum Kategotia {
		FaceBook, Messenger, WhatsUp, AppleDeveloper, GoogleAccount, VisualStudio, IntelJIdea
	};
	class Plik
	{
	private:
		MyList<string> ketogorieSTRINGS;
		std::string path;
		std::string log_path;
		std::string decodedHaslo;
		std::string lastLogin;
		Coding kod;
		bool czyHasloPrawidlowe;
		MyList<string> text;

		MyList<Haslo> getHasla();
		MyList<string> aktulizacja();
		int compareTo(codingFiles::Haslo, codingFiles::Haslo);

	public:
		Plik() : path(""), decodedHaslo(""), czyHasloPrawidlowe(false) {}
		Plik(std::string p, std::string l, Coding c);
		void rewizjaHasla(MyList<string>, int);
		void menu();
		void szukaj();
		template <typename T>
		void sortuj2Kategorii();
		void haslaPojedynczo();
		void haslaKategorii();
		void showHasla();
	};
}
