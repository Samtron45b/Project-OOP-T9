#include "Logger.hpp"

Logger *StaffLog::createInstance()
{
    if (logger == NULL)
        logger = new StaffLog;
    return logger;
}

StaffLog::StaffLog()
{
    fout.open("./data/log/stafflog.txt", ios::app);
}

void StaffLog::log(const string message)
{
    time_t t = time(0);
    struct tm *now = localtime(&t);
    fout << now->tm_year + 1900 << "/" << now->tm_mon + 1 << "/" << now->tm_wday << " ";
    fout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " ";
    fout << message << endl;
}