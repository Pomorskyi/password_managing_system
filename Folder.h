#pragma once
#include "Coding.h"
#include "MyList.h"
#include "Plik.h"
#include <string>
#include <iostream>

namespace codingFiles {
	class Folder {
	private: 
		MyList<string> filesPathes;
		codingFiles::Coding codeOfLogFile;
		string logFileName;
		string path;
		int filesNum;
		Plik curPlik;
		bool isClearFolder;

	public:
		Folder() : logFileName(""), path(""), filesNum(0) {};
		Folder(codingFiles::Coding code, string pat, string logFileName = "log.txt");
		void menu();
		
	};
}

