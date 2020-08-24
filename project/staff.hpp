#include "guest.cpp"
#include "guest.hpp"
#include "person.cpp"
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
    staff();
    staff(int id);
    ~staff();
    void input();
    void output();
    void checkIn();
    void addNewMem();
    void showMem();
    void updateMem();
    void updateRecord();            // OK
    bool deleteRecord();            //OK
    pair<item, int> searchRecord(); // OK
    void menu();
    void save();
    void get(int ID); // Not Override yet!
};