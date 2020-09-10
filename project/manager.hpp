#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

#include "staff.hpp"
#include <vector>
#include <direct.h>
#include <filesystem>
class manager : public person
{
private:
    int id;

public:
    void input();
    void output();
    void addNewStaff();
    void updateStaff();
    void deleteStaff();
    vector<double> monthlySales(); // ???
    void menu();
    void save();
    void get(int ID); // DO NOT KNOW WHAT TO CODE HERE
};

bool checkStaffID(int id, bool save, int type);
void saveStaffIDlist(int *list, int n, int type);
void deleteStaffID(int id, int type);
// NEED A ID DELETE FUNCTION

#endif // !_MANAGER_HPP_