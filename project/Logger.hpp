#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

class Logger
{
protected:
    static Logger *logger;
    Logger() {}

public:
    virtual void log(const string message){};
    virtual ~Logger() {}
    virtual Logger *createInstance() { return logger; }
    virtual void destroyInstance()
    {
        delete logger;
        logger = NULL;
    }
};

class StaffLog : public Logger
{
private:
    static ofstream fout;
    StaffLog();

public:
    friend class Logger;
    static Logger *createInstance();
    void log(const string message);
    void destroyInstance()
    {
        Logger::destroyInstance();
    }
    ~StaffLog(){};
};
#endif // !_LOGGER_H_
