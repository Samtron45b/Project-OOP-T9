#include "item.hpp"
#include <iostream>
#include "Account.h"
#include <filesystem>
using namespace std;
person* Account::myMan=nullptr;
namespace fs = ::filesystem;
int main()
{
	Account::menu();
	return 0;
}