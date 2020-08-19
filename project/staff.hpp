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
    member updateMem();
    void updateRecord();
    bool deleteRecord();
    pair<item, int> searchRecord();
    void menu();
    void save();
};