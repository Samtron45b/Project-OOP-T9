#ifndef _MYLIB_H_
#define _MYLIB_H_

#include <tuple>
#include <string>

std::tuple<int,int,int> currentTime(bool per12);
int makeFolder(const std::string& s);
bool makeDir(const std::string& dir);
void clearConsole();

class Random{
    public:
        Random();
        int next();
        int next(int);
        int next(int,int);
        double nextDouble();
};

#endif // !_MYLIB_H_
