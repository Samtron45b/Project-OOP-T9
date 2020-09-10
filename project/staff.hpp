#ifndef _STAFF_HPP_
#define _STAFF_HPP_

#include "myLib.hpp"
#include "guest.hpp"
#include "person.hpp"
#include "item.hpp"
#include <algorithm>
#include <utility>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

class staff : public person
{
private:
    string id;

public:
    staff(){};
    staff(int id);
    ~staff(){};
    void input();
    void output();
    void checkIn();
    void addNewMem();
    void showMem();
    void updateMem();
    void inputItem();
    void updateRecord();            // OK
    bool deleteRecord();            //OK
    pair<item, int> searchRecord(); // OK
    void menu();
    void save();
    void get(int ID); // Not Override yet!
};
bool is_Number(const string &s);

#endif // ! _STAFF_HPP_