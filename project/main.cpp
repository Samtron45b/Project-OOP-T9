#include "item.hpp"
#include <iostream>
#include "Account.h"
#include <filesystem>
#include "Logger.hpp"
using namespace std;
person *Account::myMan = nullptr;
namespace fs = ::filesystem;

Logger *Logger::logger = NULL;
ofstream StaffLog::fout;
int main()
{
	Account::menu();
	return 0;
}