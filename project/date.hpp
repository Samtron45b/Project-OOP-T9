#ifndef DATE_H_
#define DATE_H_

#include <iostream>

struct date
{
    int year,month,day;

    date();
    date(int y,int m,int d);

    int maxDay();

    bool leapYear();

    bool operator==(const date& rhs);
    bool operator!=(const date& rhs);
    bool operator<=(const date& rhs);
    bool operator>=(const date& rhs);
    bool operator<(const date& rhs);
    bool operator>(const date& rhs);

    bool birthdayMonth();

    friend std::istream& operator>>(std::istream& in, date& a);
    friend std::ostream& operator<<(std::ostream& out,const date a);
    float age(bool);
};


#endif // !date_H_
