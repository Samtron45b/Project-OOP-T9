#include "date.hpp"
#include <ctime>
#include <fstream>
using namespace std;

// ? Optional

void date::right()
{
    if(year<1) year=1;
    if(month<1)
    {
        month=1;
    }
    else if (month>12)
    {
        month=12;
    }
    if(day<=0)
    {
        day=1;
    }
    else if(day>date(year,month,1).maxDay())
    {
        day=1;
    }
}

date::date()
{
    time_t t =time(0);
    struct tm* now =localtime(&t);
    year=now->tm_year+1900;
    month=now->tm_mon+1;
    day=now->tm_mday;
}
date::date(int y,int m,int d)
{
    year=y;
    month=m;
    day=d;
}

int date::maxDay()
{
    if((month==1)||(month==3)||(month==5)||(month==7)||(month==8)||(month==10)||(month==12))
    {
        return 31;
    }
    else if(month==2)
    {
        if(leapYear())
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    else
    {
        return 30;
    }
}

bool date::leapYear()
{
    if((year%4==0&&year%100!=0)||year%400==0)
    {
        return true;
    }
    return false;
}

bool date::operator==(const date& rhs)
{
    if(year==rhs.year&&month==rhs.month&&day==rhs.day)
        return true;
    return false;
}
bool date::operator!=(const date& rhs)
{
    if(year!=rhs.year||month!=rhs.month||day!=rhs.day)
        return true;
    return false;
}
bool date::operator<=(const date& rhs)
{
    if(year>rhs.year) return false;

    if(year<rhs.year) return true;

    if(month>rhs.month) return false;

    if(month<rhs.month) return true;

    return day<=rhs.day;
}
bool date::operator>=(const date& rhs)
{
    if(year<rhs.year) return false;

    if(year>rhs.year) return true;

    if(month<rhs.month) return false;

    if(month>rhs.month) return true;

    return day>=rhs.day;
}
bool date::operator<(const date& rhs)
{
    if(year>rhs.year) return false;

    if(year<rhs.year) return true;

    if(month>rhs.month) return false;

    if(month<rhs.month) return true;

    return day<rhs.day;
}
bool date::operator>(const date& rhs)
{
    if(year<rhs.year) return false;

    if(year>rhs.year) return true;

    if(month<rhs.month) return false;

    if(month>rhs.month) return true;

    return day>rhs.day;
}

istream& operator>>(std::istream& in, date& a)
{
    if(&in!=&cin)
    {
        int temp;
        in>>temp;
        a.day=temp;
        in.ignore(1);
        in>>temp;
        a.month=temp;
        in.ignore(1);
        in>>temp;
        a.year=temp;
        in>>a.year>>a.month>>a.day;

    }
    else
    {
        cout<<"\tInput year: ";in>>a.year;
        cout<<"\tInput month: ";in>>a.month;
        cout<<"\tInput day: ";in>>a.day;
    }
    return in;
}
ostream& operator<<(std::ostream& out,const date& a)
{
    out<<a.day<<"/"<<a.month<<"/"<<a.year;
    return out;
}

float date::age(bool roundUp=true)
{
    date temp;
    float res;
    if(roundUp)
    {
        res=temp.year-year;
    }
    else
    {
        res =temp.year-year+(12-month+temp.month)/12.0;
    }
    return res;
}
bool date::birthdayMonth()
{
    date today;
    return (month==today.month)?true:false;
}