#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include "ListV.h"

bool ReadStr(ListH& lst, std::ifstream& f, int& bytes);

void Inf(ListV& two_list, std::ifstream& f, std::ofstream& output);

void OutStrH(ListH& lst, std::ofstream& ofile, bool isProgram);

void OutPut(ListV& two_list, std::ofstream& ofile, bool isProgram = true);