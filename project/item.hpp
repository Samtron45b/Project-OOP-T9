#ifndef ITEM_H_INCLUDED
#include <string>
#include "date.hpp"

struct item{
    std::string name;
    int id, storage;
    double price;

    item();
    item(int,std::string,int,double);
    bool get(int);
    item find(int);
    void output();
    void input();
    void update();
    bool operator==(item rhs);
    bool operator<(item rhs);
    bool operator<=(item rhs);
    bool operator>(item rhs);
    bool operator>=(item rhs);
    bool operator==(item rhs) const;
    bool operator<(item rhs) const;
    bool operator<=(item rhs) const;
    bool operator>(item rhs) const;
    bool operator>=(item rhs) const;
    friend std::ostream& operator<<(std::ostream& out,item value);
    friend std::istream& operator>>(std::istream& in,item& value);
};

#endif // !ITEM_H_INCLUDED

