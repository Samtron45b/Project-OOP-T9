#include "myLib.hpp"
#include <ctime>

using namespace std;

tuple<int,int,int> currentTime(bool per12=true)
{
    time_t t =time(0);
    struct tm* now =localtime(&t);
    int hour=now->tm_hour,min=now->tm_min,sec=now->tm_sec;
    if(per12==true)
        hour=hour%12;
    return make_tuple(hour,min,sec);
}
