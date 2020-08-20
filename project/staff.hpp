#include "guest.cpp"
#include "guest.hpp"
#include "person.cpp"
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
    ~staff();
    void input();
    void output();
    void checkIn();
    void addNewMem();
    void showMem();
    void updateMem();
    void updateRecord();            // Need Item
    bool deleteRecord();            //Need Item
    pair<item, int> searchRecord(); // Need Item
    void menu();
    void save();
};