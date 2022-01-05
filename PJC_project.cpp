#pragma once
#include <iostream>
#include <string>
#include "Folder.h"
#include "Node.h"
#include "Coding.h"
#include "MyList.h"

using namespace std;
using namespace codingFiles;


int main()
{
    string path = "D:/PJATK/2sem/PJC/PJC_project/files/";
    Coding codeOfLogFile = Coding("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-=!@#$%^&*()_+<>?,./;':[]{}", 8);
    Folder* folder = new Folder(codeOfLogFile, path);
    folder->menu();
}
