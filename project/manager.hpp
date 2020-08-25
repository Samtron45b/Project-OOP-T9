#include "staff.hpp"
#include <vector>
#include <direct.h>
class manager : public person
{
private:
    int id;

public:
    void addNewStaff();
    void updateStaff();
    void deleteStaff();
    vector<double> monthlySales; // ???
    void menu();
    void save(); // DO NOT KNOW WHAT TO CODE HERE
};

bool checkStaffID(int id, bool save);
void saveStaffIDlist(int *list, int n);
void deleteStaffID(int id);
// NEED A ID DELETE FUNCTION