#ifndef _MYLIB_H_
#define _MYLIB_H_

#include <tuple>
#include <string>
#include <random>
#include <iostream>

std::tuple<int,int,int> currentTime(bool per12);

int makeFolder(const std::string& s);
bool makeDir(const std::string& dir);
void clearConsole();

bool checkID(int ID);
void saveIDlist(int* list,int n);
class myRandom
{
    private:
        std::default_random_engine engine;

        static unsigned now();
        
    public:
        myRandom();

        int next();
        int next(int x);
        int next(int a, int b);
        double nextDouble();
};

template <typename T> bool cinIg(std::istream& stream, T& val, const bool clr = true)
    {
        stream >> val;
        bool res = !stream.fail();
        if (clr) {
            stream.clear();
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return res;
    }

#endif // !_MYLIB_H_
