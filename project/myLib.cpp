#include "myLib.hpp"
#include <ctime>
#include <iostream>
#include <chrono>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <fstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <direct.h>
    #include <windows.h>
#elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
    #include <unistd.h>
    #include <term.h>
#endif

using namespace std;

tuple<int,int,int> currentTime(bool per12)
{
    time_t t =time(0);
    struct tm* now =localtime(&t);
    int hour=now->tm_hour,min=now->tm_min,sec=now->tm_sec;
    if(per12==true)
        if(hour>12)
        hour=hour%12;
    return make_tuple(hour,min,sec);
}

int makeFolder(const std::string& s)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        return _mkdir(s.c_str());
    #elif __APPLE__
        #include <TargetConditionals.h>
        #if TARGET_IPHONE_SIMULATOR
            return 65;
        #elif TARGET_OS_IPHONE
            return 66;
        #elif TARGET_OS_MAC
            return mkdir(s.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
        #else
            #error "Unknown Apple platform"
        #endif
    #elif __linux__
        return mkdir(s.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
    #elif __unix__
        return 31;
    #elif defined(_POSIX_VERSION)
        return 32;
    #else
    #   error "Unknown compiler"
    #endif

    return 0;
}

bool makeDir(const std::string& dir)
{
    size_t pos;
    if (dir[0] == '.') pos = dir.find('/', dir.find('/') + 1);
    else pos = dir.find('/') + 1;
    while (pos < std::string::npos) {
        if (makeFolder(dir.substr(0, pos)) == 0);
        pos = dir.find('/', pos + 1);
    }
    if (makeFolder(dir) == 0) return true;
    return false;
}

void clearConsole()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        COORD topLeft  = { 0, 0 };
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        SetConsoleCursorPosition(console, topLeft);
    #elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
        if (!cur_term) {
            int result;
            setupterm(NULL, STDOUT_FILENO, &result);
            if (result <= 0) return;
        }
        putp(tigetstr( "clear" ));
    #endif // defined
}

// ! Random

unsigned myRandom::now()
{
    return std::chrono::system_clock::now().time_since_epoch().count();
}

myRandom::myRandom(): engine(now()) {};

int myRandom::next()
{
    return engine();
}

int myRandom::next(int x)
{
    std::uniform_int_distribution<int> dist(0, x);
    return dist(engine);
}

int myRandom::next(int a, int b)
{
    std::uniform_int_distribution<int> dist(a, b);
    return dist(engine);
}

double myRandom::nextDouble()
{
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(engine);
}

// ! ID List

bool checkID(int ID,int file,bool save=true)
{
    string link="data/";
    switch(file)
    {
        //! Member
        case 1:
            link+="member/ID_List.txt";
            break;
        //! item
        case 2:
            link+="item/ID_List.txt";
            break;
        default:
            break;
    }
    ifstream list(link);

    int *arr,n;
    if(list.is_open())
    {
        list>>n;
        arr=new int[n+1];
        for(int i=0;i<n;++i)
        {
            list>>arr[i];
        }
        list.close();
    }
    bool res=true;
    for(int i=0;i<n;++i)
    {
        if(arr[i]==ID)
            res=false;
    }
    if(res&&save)
    {
        arr[n]=ID;
        sort(arr,arr+n+1);
        ++n;
        saveIDlist(arr,n,link);
    }
    delete []arr;
    return res;
}
void saveIDlist(int* list,int n,string link)
{
    ofstream file(link);
    if(file.is_open())
    {
        file<<n<<endl;
        for(int i=0;i<n;++i)
        {
            file<<list[i]<<endl;
        }
        file.close();
    }
}