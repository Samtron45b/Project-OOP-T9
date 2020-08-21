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
    void save();
};

bool checkStaffID(int id);
void saveStaffIDlist(int *list, int n);